#include "grafoorientato.h" 
#include <iostream>
#include <cassert>
#include <ostream>



/*--------------------------------------*/
/*										*/
/*	FILIPPO NEMBRINI SEBASTIANO 886135	*/
/*										*/
/*--------------------------------------*/



 /**
 * @brief Crea Struct tipoSpeciale per effettuare dei test 
 * 
 * @param idInt id di tipo Int
 * @param idLong id di tipo Long
 */
struct tipoSpeciale {
    int idInt;
    long idLong;
};



/**
*	@brief Operatore di Stream
*
*	@param os stream
*	@param tipoS Struct di tipoSpeciale
*
*	@return Stream di output
*/
std::ostream &operator<<(std::ostream &os, const tipoSpeciale &tipoS) {

		os << tipoS.idInt << " " << tipoS.idLong << " ";

	return os;
}



/**
*	@brief Confronta 2 interi per vedere se sono uguali
*
*	@param a Primo Int
*	@param b Secondo Int
*	
*	@return bool in base al se sono uguali o meno
*/
struct compare_int {
	bool operator()(int a, int b) const {
		return a==b;
	}
};



/**
*	@brief Confronta 2 double per vedere se sono uguali
*
*	@param a Primo Double
*	@param b Secondo Double
*	
*	@return bool in base al se sono uguali o meno
*/
struct compare_double {
	bool operator()(double a, double b) const {
		return a==b;
	}
};



/**
*	@brief Confronta 2 tipoSpeciale per vedere se sono uguali
*
*	@param a Primo tipoSpeciale
*	@param b Secondo tipoSpeciale
*	
*	@return bool in base al se sono uguali o meno
*/
struct compare_tipoSpeciale {
	bool operator()(const tipoSpeciale &tipoSpec1, const tipoSpeciale &tipoSpec2) const {
		return (tipoSpec1.idInt == tipoSpec2.idInt && tipoSpec1.idLong == tipoSpec2.idLong);
	}
};



	/**
	* @brief Classe Iteratrice Costante Forward di tipo Int
	*/
void test_const_iterator_int(const grafo<int, compare_int> &n) {
	grafo<int, compare_int>::const_iterator it, ite;

	for(it=n.getPrimoElemento(),ite=n.getUltimoElemento(); it!=ite; ++it) {
        assert(!(it==ite));
		std::cout << "Nodo: " << *it << std::endl;
	}	
}



	/**
	* @brief Classe Iteratrice Costante Forward di tipo Double
	*/
void test_const_iterator_double(const grafo<double, compare_double> &n) {
	grafo<double, compare_double>::const_iterator it, ite;

	for(it=n.getPrimoElemento(),ite=n.getUltimoElemento(); it!=ite; ++it) {
        assert(!(it==ite));
		std::cout << "Nodo: " << *it << std::endl;
	}	
}



	/**
	* @brief Classe Iteratrice Costante Forward di tipo Int
	*/
void test_const_iterator_tipoSpeciale(const grafo<tipoSpeciale, compare_tipoSpeciale> &n) {
	grafo<tipoSpeciale, compare_tipoSpeciale>::const_iterator it, ite;

	for(it=n.getPrimoElemento(),ite=n.getUltimoElemento(); it!=ite; ++it) {
        assert(!(it==ite));
		std::cout << "Nodo: " << *it << std::endl;
	}	
}



/*--------------------*/
/*   INZIO DEI TEST   */  
/*--------------------*/

	/**
	* @brief Test sui nodi Int
	*/
void test_nodi_int(){

    std::cout<<"INIZIO DEI TEST SU test_nodi_int" << std::endl;
    std::cout<<"Costruttore primario: grafo<int> nodi;" << std::endl << std::endl;
    grafo<int, compare_int> nodi;



    std::cout<<"Tento di aggiungere 3 Nodi: " << std::endl << std::endl;

    try{
        nodi.addNode(88);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==1);
    std::cout << "Aggiunto nodo 88, getCapacity: " << nodi.getCapacity() << std::endl;
    std::cout << "Risultato nodi.existsNode(88): " << nodi.existsNode(88) << std::endl << std::endl;

    std::cout << "Cerco di aggiungere di nuovo nodo 88, getCapacity: " << nodi.getCapacity() << std::endl;
    try{
        nodi.addNode(88);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==1);
    std::cout << "Risultato nodi.existsNode(88): " << nodi.existsNode(88) << std::endl << std::endl;

    try{
        nodi.addNode(61);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==2);
    std::cout << "Aggiunto nodo 61, getCapacity: " << nodi.getCapacity() << std::endl;
    std::cout << "Risultato nodi.existsNode(61): " << nodi.existsNode(61) << std::endl << std::endl;

    try{
        nodi.addNode(35);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==3);
    std::cout << "Aggiunto nodo 35, getCapacity: " << nodi.getCapacity() << std::endl;
    std::cout << "Risultato nodi.existsNode(35): " << nodi.existsNode(35) << std::endl << std::endl;



    std::cout << "Risultato nodi.existsEdge(88, 61): " << nodi.existsEdge(88, 61) << std::endl << std::endl;



    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl;

    try{
        nodi.addEdge(88, 35);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco 88->35, nodi.existsEdge(88, 35): " << nodi.existsEdge(88, 35) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.removeEdge(88, 35);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Rimosso arco 88->35, nodi.existsEdge(88, 35): " << nodi.existsEdge(88, 61) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    std::cout << "Cerco di rimuovere di nuovo arco 88->35, nodi.existsEdge(88, 35): " << nodi.existsEdge(88, 61) << std::endl;
    try{
        nodi.removeEdge(88, 35);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.addEdge(61, 88);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco 61->88, nodi.existsEdge(61, 88): " << nodi.existsEdge(61, 88) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.addEdge(88, 88);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;     
    }    
    std::cout << "Aggiunto arco 88->88, nodi.existsEdge(88, 88): " << nodi.existsEdge(88, 88) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.addEdge(61, 61);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    } 
    std::cout << "Aggiunto arco 61->61, nodi.existsEdge(61, 61): " << nodi.existsEdge(61, 61) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl ;

    std::cout << "Aggiunto ancora arco 61->61, nodi.existsEdge(61, 61): " << nodi.existsEdge(61, 61) << std::endl;
    try{
        nodi.addEdge(61, 61);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    } 
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.removeNode(61);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }     
    std::cout << "Rimosso nodo 61, nodi.getCapacity(): " << nodi.getCapacity() << std::endl << std::endl;
    std::cout << "Numero di Nodi: " << nodi.getCapacity() << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;


    std::cout << "Cerco di rimuoveredi nuovo nodo 61, nodi.getCapacity(): " << nodi.getCapacity() << std::endl;
    try{
        nodi.removeNode(61);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl << std::endl;
    }      
    std::cout << "Numero di Nodi: " << nodi.getCapacity() << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl;

    std::cout << "Risultato nodi.existsEdge(88, 35): " << nodi.existsEdge(88, 35) << std::endl << std::endl;



    grafo<int, compare_int> nodi2;
    nodi2 = nodi;
    std::cout << "Assegnamento, getCapacity: " << nodi2.getCapacity() << std::endl << std::endl;



    grafo<int, compare_int> nodi3(nodi2);
    std::cout << "Copy constructor, getCapacity: " << nodi2.getCapacity() << std::endl << std::endl;

    test_const_iterator_int(nodi);

    std::cout<< nodi << std::endl << std::endl;

    std::cout<<"FINE DEI TEST SU test_nodi_int" << std::endl << std::endl;
    std::cout<<"----------------------------------------------------------" << std::endl << std::endl;
}




	/**
	* @brief Test sui nodi Double
	*/
void test_nodi_double(){

    std::cout<<"INIZIO DEI TEST SU test_nodi_double" << std::endl;

    std::cout<<"Costruttore primario: grafo<double> nodi;" << std::endl << std::endl;
    grafo<double, compare_double> nodi;




    std::cout<<"Tento di aggiungere 3 Nodi: " << std::endl << std::endl;

    try{
        nodi.addNode(8.8);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==1);
    std::cout << "Aggiunto nodo 8.8, getCapacity: " << nodi.getCapacity() << std::endl;
    std::cout << "Risultato nodi.existsNode(8.8): " << nodi.existsNode(8.8) << std::endl << std::endl;

    std::cout << "Cerco di aggiungere di nuovo nodo 8.8, getCapacity: " << nodi.getCapacity() << std::endl;
    try{
        nodi.addNode(8.8);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==1);
    std::cout << "Risultato nodi.existsNode(8.8): " << nodi.existsNode(8.8) << std::endl << std::endl;

    try{
        nodi.addNode(6.1);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==2);
    std::cout << "Aggiunto nodo 6.1, getCapacity: " << nodi.getCapacity() << std::endl;
    std::cout << "Risultato nodi.existsNode(6.1): " << nodi.existsNode(6.1) << std::endl << std::endl;

    try{
        nodi.addNode(3.5);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==3);
    std::cout << "Aggiunto nodo 3.5, getCapacity: " << nodi.getCapacity() << std::endl;
    std::cout << "Risultato nodi.existsNode(3.5): " << nodi.existsNode(3.5) << std::endl << std::endl;



    std::cout << "Risultato nodi.existsEdge(8.8, 6.1): " << nodi.existsEdge(8.8, 6.1) << std::endl << std::endl;



    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl;

    try{
        nodi.addEdge(8.8, 3.5);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco 8.8->3.5, nodi.existsEdge(8.8, 3.5): " << nodi.existsEdge(8.8, 3.5) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.removeEdge(8.8, 3.5);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Rimosso arco 8.8->3.5, nodi.existsEdge(8.8, 3.5): " << nodi.existsEdge(8.8, 6.1) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    std::cout << "Cerco di rimuovere di nuovo arco 8.8->3.5, nodi.existsEdge(8.8, 3.5): " << nodi.existsEdge(8.8, 6.1) << std::endl;
    try{
        nodi.removeEdge(8.8, 3.5);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.addEdge(6.1, 8.8);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco 6.1->8.8, nodi.existsEdge(6.1, 8.8): " << nodi.existsEdge(6.1, 8.8) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.addEdge(8.8, 8.8);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;     
    }    
    std::cout << "Aggiunto arco 8.8->8.8, nodi.existsEdge(8.8, 8.8): " << nodi.existsEdge(8.8, 8.8) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.addEdge(6.1, 6.1);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    } 
    std::cout << "Aggiunto arco 6.1->6.1, nodi.existsEdge(6.1, 6.1): " << nodi.existsEdge(6.1, 6.1) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl ;

    std::cout << "Aggiunto ancora arco 6.1->6.1, nodi.existsEdge(6.1, 6.1): " << nodi.existsEdge(6.1, 6.1) << std::endl;
    try{
        nodi.addEdge(6.1, 6.1);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    } 
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    try{
        nodi.removeNode(6.1);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }     
    std::cout << "Rimosso nodo 6.1, nodi.getCapacity(): " << nodi.getCapacity() << std::endl << std::endl;
    std::cout << "Numero di Nodi: " << nodi.getCapacity() << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;


    std::cout << "Cerco di rimuoveredi nuovo nodo 6.1, nodi.getCapacity(): " << nodi.getCapacity() << std::endl;
    try{
        nodi.removeNode(6.1);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl << std::endl;
    }      
    std::cout << "Numero di Nodi: " << nodi.getCapacity() << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl;

    std::cout << "Risultato nodi.existsEdge(8.8, 3.5): " << nodi.existsEdge(8.8, 3.5) << std::endl << std::endl;




    grafo<double, compare_double> nodi2;
    nodi2 = nodi;
    std::cout << "Assegnamento, getCapacity: " << nodi2.getCapacity() << std::endl << std::endl;

    grafo<double, compare_double> nodi3(nodi2);
    std::cout << "Copy constructor, getCapacity: " << nodi2.getCapacity() << std::endl << std::endl;

    test_const_iterator_double(nodi2);

    std::cout<< nodi << std::endl << std::endl;

    std::cout<<"FINE DEI TEST SU test_nodi_double" << std::endl << std::endl;
    std::cout<<"----------------------------------------------------------" << std::endl << std::endl;

}



	/**
	* @brief Test sui nodi tipoSpeciale
	*/
void test_nodes_tipoSpeciale(){

    std::cout<<"INIZIO DEI TEST SU test_nodi_tipoSpeciale" << std::endl;
    std::cout<<"Costruttore primario: grafo<tipoSpeciale, compare_tipoSpeciale> nodi;" << std::endl << std::endl;
    grafo<tipoSpeciale, compare_tipoSpeciale> nodi;



    tipoSpeciale tipoSpec1;
    tipoSpec1.idInt=1;
    tipoSpec1.idLong=2;

    tipoSpeciale tipoSpec2;
    tipoSpec2.idInt=2;
    tipoSpec2.idLong=2;

    tipoSpeciale tipoSpec3;
    tipoSpec3.idInt=10;
    tipoSpec3.idLong=1;



    std::cout<<"Tento di aggiungere 3 Nodi: " << std::endl << std::endl;
    try{
        nodi.addNode(tipoSpec1);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==1);
    std::cout << "Aggiunto nodo tipoSpec1, getCapacity: " << nodi.getCapacity() << std::endl;
    std::cout << "idInt: " << tipoSpec1.idInt << std::endl;
    std::cout << "idLong: " << tipoSpec1.idLong << std::endl << std::endl ;
    


    std::cout << "Cerco di aggiungere di nuovo nodo tipoSpec1, getCapacity: " << nodi.getCapacity() << std::endl;
    try{
        nodi.addNode(tipoSpec1);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==1);
    std::cout << "Risultato nodi.existsNode(tipoSpec1): " << nodi.existsNode(tipoSpec1) << std::endl << std::endl ;
    
    

    try{
        nodi.addNode(tipoSpec2);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==2);
    std::cout << "Aggiunto nodo tipoSpec2, getCapacity: " << nodi.getCapacity() << std::endl;
    std::cout << "idInt: " << tipoSpec2.idInt << std::endl;
    std::cout << "idLong: " << tipoSpec2.idLong << std::endl;
    std::cout << "Risultato nodi.existsNode(tipoSpec2): " << nodi.existsNode(tipoSpec2) << std::endl << std::endl ;
    


    try{
        nodi.addNode(tipoSpec3);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    assert(nodi.getCapacity()==3);
    std::cout << "Aggiunto nodo tipoSpec3, getCapacity: " << nodi.getCapacity() << std::endl;
    std::cout << "idInt: " << tipoSpec3.idInt << std::endl;
    std::cout << "idLong: " << tipoSpec3.idLong << std::endl << std::endl;
    std::cout << "Risultato nodi.existsNode(tipoSpec3): " << nodi.existsNode(tipoSpec3) << std::endl << std::endl ;



    std::cout << "Risultato nodi.existsEdge(tipoSpec1, tipoSpec2): " << nodi.existsEdge(tipoSpec1, tipoSpec2) << std::endl << std::endl ;
    
    

    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl;
    
    try{
        nodi.addEdge(tipoSpec1, tipoSpec3);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco tipoSpec1->tipoSpec3, nodi.existsEdge(tipoSpec1, tipoSpec3): " << nodi.existsEdge(tipoSpec1, tipoSpec3) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl ;



    try{
        nodi.removeEdge(tipoSpec1, tipoSpec3);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Rimosso arco tipoSpec1->tipoSpec3, nodi.existsEdge(tipoSpec1, tipoSpec3): " << nodi.existsEdge(tipoSpec1, tipoSpec2) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;



    std::cout << "Cerco di rimuovere di nuovo arco tipoSpec1->tipoSpec3, nodi.existsEdge(tipoSpec1, tipoSpec3): " << nodi.existsEdge(tipoSpec1, tipoSpec3) << std::endl;
    try{
        nodi.removeEdge(tipoSpec1, tipoSpec3);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;
    
    
    
    try{
        nodi.addEdge(tipoSpec2, tipoSpec1);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco tipoSpec2->tipoSpec1, nodi.existsEdge(tipoSpec2, tipoSpec1): " << nodi.existsEdge(tipoSpec2, tipoSpec1) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;

    
    try{
        nodi.addEdge(tipoSpec1, tipoSpec1);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco tipoSpec1->tipoSpec1, nodi.existsEdge(tipoSpec1, tipoSpec1): " << nodi.existsEdge(tipoSpec1, tipoSpec1) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;
    
    
    try{
        nodi.addEdge(tipoSpec2, tipoSpec2);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Aggiunto arco tipoSpec2->tipoSpec1, nodi.existsEdge(tipoSpec2, tipoSpec2): " << nodi.existsEdge(tipoSpec2, tipoSpec2) << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;
    
    
    
    std::cout << "Aggiungo di nuovo arco tipoSpec2->tipoSpec1, nodi.existsEdge(tipoSpec2, tipoSpec2): " << nodi.existsEdge(tipoSpec2, tipoSpec2) << std::endl << std::endl;
    try{
        nodi.addEdge(tipoSpec2, tipoSpec2);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;



    try{
        nodi.removeNode(tipoSpec2);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Rimuovo nodo tipoSpec2, nodi.getCapacity(): " << nodi.getCapacity() << std::endl;
    std::cout << "Numero di Nodi: " << nodi.getCapacity() << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;


    std::cout << "Cerco di rimuovere ancora nodo tipoSpec2, nodi.getCapacity(): " << nodi.getCapacity() << std::endl;
    try{
        nodi.removeNode(tipoSpec2);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Numero di Nodi: " << nodi.getCapacity() << std::endl;
    std::cout << "Numero di Archi: " << nodi.getEdgesNum() << std::endl << std::endl;



    std::cout << "Risultato nodi.existsEdge(tipoSpec1, tipoSpec3): " << nodi.existsEdge(tipoSpec1, tipoSpec3) << std::endl << std::endl;



    grafo<tipoSpeciale, compare_tipoSpeciale> nodi2;
    nodi2 = nodi;
    std::cout << "Assegnamento, getCapacity: " << nodi2.getCapacity() << std::endl << std::endl;



    grafo<tipoSpeciale, compare_tipoSpeciale> nodi3(nodi2);
    std::cout << "Copy constructor, getCapacity: " << nodi2.getCapacity() << std::endl << std::endl;

    test_const_iterator_tipoSpeciale(nodi);

    std::cout<< nodi << std::endl << std::endl;

    std::cout<<"FINE DEI TEST SU test_nodi_tipoSpeciale" << std::endl << std::endl;
    std::cout<<"----------------------------------------------------------" << std::endl << std::endl;
}



	/**
	* @brief Main
	*/
int main(int argc, char *argv[]) {

	std::cout<<"INIZIO DEI TEST SU grafoorientato.h" << std::endl << std::endl;

    std::cout<<"----------------------------------------------------------" << std::endl << std::endl;



    test_nodi_int();



    test_nodi_double();



    test_nodes_tipoSpeciale();



    std::cout<<"----------------------------------------------------------" << std::endl << std::endl;

    std::cout<<"FINE DEI TEST SU grafoorientato.h" << std::endl;

    return 0;
}