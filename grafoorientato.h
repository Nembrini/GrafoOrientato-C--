#ifndef GRAFOORIENTATO_H
#define GRAFOORIENTATO_H



/*--------------------------------------*/
/*										*/
/*	FILIPPO NEMBRINI SEBASTIANO 886135	*/
/*										*/
/*--------------------------------------*/




#include <ostream>
#include <iostream>
#include <iterator> 
#include <cstddef>  
#include <stdexcept>
#include <string>


 /**
 * @brief Eccezione che si verifica quando il nodo esiste di già
 * 
 * @return message Messaggio che appare a schermo 
 */
class nodeAlreadyExistsException final : public std::exception {
private:
    const char* message = "Il nodo che stai provando ad inserire esiste di già.";
public:
    virtual const char* what() const noexcept {
        return message;
    }
};



 /**
 * @brief Eccezione che si verifica quando l'arco esiste di già
 * 
 * @return message Messaggio che appare a schermo 
 */
class edgeAlreadyExistsException final : public std::exception {
private:
    const char* message = "L'arco che stai provando ad inserire esiste di già.";
public:
    virtual const char* what() const noexcept {
        return message;
    }
};



 /**
 * @brief Eccezione che si verifica quando il nodo non esiste
 * 
 * @return message Messaggio che appare a schermo 
 */
class nodeDontExistsException final : public std::exception {
private:
    const char* message = "Il nodo scelto non esiste.";
public:
    virtual const char* what() const noexcept {
        return message;
    }
};



 /**
 * @brief Eccezione che si verifica quando l'arco non esiste
 * 
 * @return message Messaggio che appare a schermo 
 */
class edgeDontExistsException final : public std::exception {
private:
    const char* message = "L'arco scelto non esiste.";
public:
    virtual const char* what() const noexcept {
        return message;
    }
};





/**
*	@brief Classe che rappresenta un insieme di nodi.
*
*	@param T tipo del dato
*	@param C comparazione 
*/
template <typename T, typename C>
class grafo {

public:

	typedef T idNode; ///< Tipo usato come Identificatore dei Nodi
	typedef unsigned int size_type; ///< Tipo usato per le Dimensioni
	typedef C comparator; ///< Tipo usato per la comparazione
	


private:

	size_type capacity; ///< Numero di nodi nel grafo
	idNode *setOfNodes; ///< Puntatore all'array contente i Nodi del Grafo
	bool **adjacencyMatrix; ///< Puntatore alla matrice d'adiacenza contenente gli archi



public:

	/**
	*	@brief Costruttore di default.
	*	
	*	@param 	capacity Numero di nodi nel grafo
	*	@param	adjacencyMatrix	Matrice d'adiacenza contenente gli archi
	*	@param	setOfNodes	Array contente i Nodi del Grafo
	*
	*	@post setOfNodes==nullptr
	*	@post adjacencyMatrix==nullptr
	*	@post capacity==0
	*/
	grafo() : capacity(0), setOfNodes(nullptr), adjacencyMatrix(nullptr) {}



	/*
	*	Distruttore
	*/
	~grafo() {
		clearMatrix();
	}



	/**
	*	@brief Operatore di assegnamento.
	*	
	*	@param 	other Reference ad un altro grafo
	*
	*	@return this
	*/
	grafo& operator=(const grafo &other) {

        #ifndef NDEBUG
        std::cout << "Copia di un grafo in corso:" << std::endl;
        #endif

		if (this != &other) {
			grafo tmp(other);
			std::swap(this->capacity,tmp.capacity);
			std::swap(this->setOfNodes,tmp.setOfNodes);
			std::swap(this->adjacencyMatrix,tmp.adjacencyMatrix);
		}

		return *this;
	}



	/**
	*	@brief Copy Constructor
	*
	*	@param other Nodo da copiare
	*
	*	@throw Eccezione di Allocazione della Memoria
	*/
	grafo(const grafo& other) : capacity(0), setOfNodes(nullptr), adjacencyMatrix(nullptr) {
		try{
			//Insieme di nodi
			setOfNodes = new idNode[other.capacity];
			for(size_type i = 0; i < other.capacity; ++i){
				setOfNodes[i] = other.setOfNodes[i];
			}

			//Matrice di archi
			adjacencyMatrix = new bool*[other.capacity];
			for(size_type i = 0; i < other.capacity; ++i){
				adjacencyMatrix[i] = nullptr;
			}
			for(size_type i = 0; i < other.capacity; ++i){
				adjacencyMatrix[i] = new bool[other.capacity];
			}
			for(size_type i = 0; i < other.capacity; ++i){
				for(size_type j = 0; j < other.capacity; ++j){
					adjacencyMatrix[i][j] = other.adjacencyMatrix[i][j];
				}
			}

			capacity = other.capacity;
		}catch(...) {
			clearMatrix();
			throw;
		}

	}

	/**
	*	@brief  Getter del Numero di Archi
	*
	*	@return Numero di Archi 
	*/
    size_type getEdgesNum() const {
        int edgeCount = 0;
        for (size_type i = 0; i < capacity; ++i)
            for (size_type j = 0; j < capacity; ++j)
                if (adjacencyMatrix[i][j])
                    ++edgeCount;
        return edgeCount;
    }



	/**
	*	@brief  Getter del Numero di Nodi
	*
	*	@return Numero di Nodi 
	*/
	size_type getCapacity() const {
		return capacity;
	}

	

	/**
	*	@brief  Setter del Numero di Nodi
	*/
    void setCapacity(int newCapacity) {
        if (newCapacity >= 0) {
            capacity = newCapacity;
            std::cout << "Capacità impostata a: " << capacity << std::endl;
        } else {
            std::cerr << "Errore: la capacità deve essere un numero positivo." << std::endl;
        }
    }



	/**
	* @brief Classe Iteratrice Costante Forward
	*/

	class const_iterator {
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		/**
		*	@brief Costruttore di Default
		*/
		const_iterator() : ptr(nullptr) {
		}
		


		/**
		*	@brief Costruttore di Copia
		*/
		const_iterator(const const_iterator &other) : ptr(other.ptr) {
		}



		/**
		*	@brief Operatore di assegnamento
		*/
		const_iterator& operator=(const const_iterator &other) {
			ptr = other.ptr;
			return *this;
		}



		/**
		*	@brief Distruttore
		*/
		~const_iterator() {}


		/**
		*	@brief Operatore di dereferenziamento
		*/
		reference operator*() const {
			return *ptr;
		}



		/**
	    *	@brief Operatore freccia
     	*/
		pointer operator->() const {
			return ptr;
		}
		


		/**
		*	@brief Operatore di iterazione post-incremento
		*/
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			++ptr;
			return tmp;
		}



		/**
		*	@brief Operatore di iterazione post-incremento
		*/
		const_iterator& operator++() {
			++ptr;
			return *this;
		}



		/**
		*	@brief Operatore di uguaglianza
		*/
		bool operator==(const const_iterator &other) const {
			return (ptr == other.ptr);
		}
		


		/**
    	*	@brief Operatore di diversità
		*/
		bool operator!=(const const_iterator &other) const {
			return (ptr != other.ptr);
		}

	private:
		const T *ptr;

		friend class grafo; 

		const_iterator(const T* p) : ptr(p) { }
	};



	/**
	* 	@brief Metodo inizio dei nodi
	*
	*	@return Iteratore all'inizio della sequenza dati
	*/
	const_iterator getPrimoElemento() const {
		return const_iterator(setOfNodes);
	}
	


	/**
	* 	@brief Metodo inizio dei nodi
	*
	*	@return Iteratore alla fine della sequenza dati
	*/

	const_iterator getUltimoElemento() const {
		return const_iterator(setOfNodes+capacity);
	}



	/**
	*	@brief Aggiunta di un Nodo
	*
	*	@param i id del Nodo
	*
	*	@throw Eccezione: Nodo già esistente
	*	@throw Eccezione di Allocazione della Memoria
	*/
	void addNode(const idNode &i){
        if(!existsNode(i)){
            if(capacity==0){
                try{
                    setOfNodes = new idNode[1];
                    setOfNodes[0]=i;
                    ++capacity;
                    adjacencyMatrix = new bool*[capacity];
                    for(size_type c = 0; c < capacity; ++c){
                        adjacencyMatrix[c] = nullptr;
                    }
                    for(size_type c = 0; c < capacity; ++c){
                        adjacencyMatrix[c] = new bool[capacity];
                    }
                }catch(const std::bad_alloc& e) {
                    clearMatrix();
                    throw;
                }
                adjacencyMatrix[0][0] = false;
            }else{
                try{
                    idNode *_setOfNodes = new idNode[capacity+1];
                    for(size_type c = 0; c < capacity; ++c){
                        _setOfNodes[c] = setOfNodes[c];
                    }
                    _setOfNodes[capacity] = i;
                    ++capacity;
                    delete[] setOfNodes;
                    setOfNodes = _setOfNodes;
                    bool **tmpArcs = new bool*[capacity];
                    for(size_type c = 0; c < capacity; ++c){
                        tmpArcs[c] = nullptr;
                    }
                    for(size_type c = 0; c < capacity; ++c){
                        tmpArcs[c] = new bool[capacity];
                    }
                    for(size_type c = 0; c < capacity-1; ++c){
                        for(size_type j = 0; j < capacity-1; ++j){
                            tmpArcs[c][j] = adjacencyMatrix[c][j];
                        }
                        tmpArcs[c][capacity-1] = 0;
                    }
                    for(size_type c = 0; c < capacity; ++c){
                        tmpArcs[capacity-1][c] = 0;
                    }
                    for(size_type c = 0; c < capacity-1; ++c){
                        delete[] adjacencyMatrix[c];
                    }
                    delete[] adjacencyMatrix;
                    adjacencyMatrix = nullptr;
                    adjacencyMatrix = tmpArcs;
                }catch(const std::bad_alloc& e){
                    clearMatrix();
                    throw;
                }
            }
        }else{
            throw nodeAlreadyExistsException();
        }
    }



	/**
	*	@brief Rimozione di un Nodo
	*
	*	@param i id del Nodo
	*
	*	@throw Eccezione: Nodo non esistente
	*	@throw Eccezione di Allocazione della Memoria
	*/
	void removeNode(const idNode &i){
		if(existsNode(i)){
			if(capacity==1){
				delete[] adjacencyMatrix[0];
				adjacencyMatrix[0]=nullptr;
				delete[] adjacencyMatrix;
				adjacencyMatrix=nullptr;
				delete[] setOfNodes;
				setOfNodes=nullptr;
				--capacity;
			}else{
				size_type posId = getNodePosition(i);

				try{

					//Insieme di nodi
					idNode *_setOfNodes = new idNode[(this->capacity)-1];

					size_type d = 0;
					for(size_type c = 0; c < capacity+1; ++c){
						if(c==posId){
							--capacity;
						}else{
							_setOfNodes[d] = setOfNodes[c];
							++d;
						}
					}
					delete[] setOfNodes;
					setOfNodes = _setOfNodes;

					//Matrice di archi
					bool **tmpArcs = new bool*[capacity];

					for(size_type i = 0; i < capacity; ++i){
						tmpArcs[i] = nullptr;
					}

					for(size_type i = 0; i < capacity; ++i){
						tmpArcs[i] = new bool[capacity];
					}

					size_type cTmp = 0;
					size_type jTmp = 0;
					for(size_type c = 0; c < capacity+1; ++c){
						jTmp = 0;
						if(posId!=c){
							for(size_type j = 0; j < capacity+1; ++j){
								if(posId!=j){
								tmpArcs[cTmp][jTmp] = adjacencyMatrix[c][j];
								++jTmp;
								}
							}
							++cTmp;
						}
					}
					
					for(size_type c = 0; c < capacity+1; ++c){
						delete[] adjacencyMatrix[c];
					}
					delete[] adjacencyMatrix;
					adjacencyMatrix = nullptr;

					adjacencyMatrix = tmpArcs;

				}catch(...){
					clearMatrix();
					throw;
				}
			}
		}else{
            throw nodeDontExistsException();
		}
	}




	/**
	*	@brief Aggiunta di un Arco
	*
	*	@param startingId id del Primo Nodo dell'Arco 
	*	@param endingId id del Secondo Nodo dell'Arco 
	*
	*	@throw Eccezione: Nodo non esistente
	*	@throw Eccezione: Arco già esistente
	*/
	void addEdge(const idNode &startingId, const idNode &endingId){
        bool startingNodeExists = existsNode(startingId);
        bool arrivalNodeExists = existsNode(endingId);
        size_type posStarting = getNodePosition(startingId);
        size_type posArrival = getNodePosition(endingId);

        if(startingNodeExists && arrivalNodeExists && !adjacencyMatrix[posStarting][posArrival]){
            adjacencyMatrix[posStarting][posArrival] = true;
        }else if (!startingNodeExists||!arrivalNodeExists)
		{
			throw nodeDontExistsException();
		}
		else{
			throw edgeAlreadyExistsException();
		}
    }



	/**
	*	@brief Rimozione di un Arco
	*
	*	@param startingId id del Primo Nodo dell'Arco 
	*	@param endingId id del Secondo Nodo dell'Arco 
	*
	*	@throw Eccezione: Nodo non esistente
	*	@throw Eccezione: Arco non esistente
	*/
    void removeEdge(const idNode &startingId, const idNode &endingId){
        bool startingNodeExists = existsNode(startingId);
        bool arrivalNodeExists = existsNode(endingId);
        bool arcExists = existsEdge(startingId, endingId);

        if(startingNodeExists && arrivalNodeExists && arcExists){

            size_type startingPos = getNodePosition(startingId);
            size_type arrivalPos = getNodePosition(endingId);
            adjacencyMatrix[startingPos][arrivalPos] = false;

        }else if (!startingNodeExists||!arrivalNodeExists)
		{
			throw nodeDontExistsException();
		}
		else{
			throw edgeDontExistsException();
		}
    }



	/**
	*	@brief Cancellazione del Grafo
	*/
    void clearMatrix(){
      if (adjacencyMatrix != nullptr) {
        for(size_type i = 0; i < capacity; ++i){
          delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
        adjacencyMatrix = nullptr;
      }
      if (setOfNodes != nullptr) {
        delete[] setOfNodes;
        setOfNodes = nullptr;
      }
      setCapacity(0);
    }



	/**
	*	@brief Verifica dell'esistenza di un Nodo
	*
	*	@param i id del Nodo
	*	
	*	@return bool in base all'esistenza o meno del Nodo
	*/
    bool existsNode(const idNode &i) const {
      comparator comp;

      for(size_type c = 0; c < capacity; ++c){
        if(comp(this->setOfNodes[c], i)){
          return true;
        }
      }
      return false;
    }



	/**
	*	@brief Verifica dell'esistenza di un Arco
	*
	*	@param startingId id del Primo Nodo dell'Arco 
	*	@param endingId id del Secondo Nodo dell'Arco 
	*	
	*	@return bool in base all'esistenza o meno dell'Arco
	*/
    bool existsEdge(const idNode &startingId, const idNode &endingId) const {
        bool nodesExist = existsNode(startingId) && existsNode(endingId);

        if(nodesExist){
            size_type posStarting = getNodePosition(startingId);
            size_type posArrival = getNodePosition(endingId);
            return adjacencyMatrix[posStarting][posArrival];
        }
        return false;
    }



private:

	/**
	*	@brief Trova la posizione di un nodo all'interno dell'array.
	*
	*	@param i id del Nodo da cercare
	*	
	*	@return size_type Posizione del nodo
	*/
	size_type getNodePosition(const idNode &i) const {
		comparator comp;

		for(size_type c = 0; c < capacity; ++c){
			if(comp(this->setOfNodes[c], i)){
				return c;
			}
		}
        return -1;
	}


	
	/**
	*	@brief Verifica la validità del valore di un Nodo
	*
	*	@param value id del Nodo da cercare
	*	
	*	@return bool se è valido o meno
	*/
    bool validateNodeValue(int value) const {
        return (value == true || value == false);
    }

}; 



	/**
	*	@brief Operatore di Stream
	*
	*	@param os stream
	*	@param graph Grafo da stampare
	*
	*	@return Stream di output
	*/
template <typename T, typename E>
std::ostream &operator<<(std::ostream &os, 
	const grafo<T, E> &graph) {

    typename grafo<T, E>::const_iterator i, ie;
	for (i = graph.getPrimoElemento(), ie = graph.getUltimoElemento(); i != ie; ++i)
		os << *i << " ";
	return os;
}




#endif // GRAFOORIENTATO_H