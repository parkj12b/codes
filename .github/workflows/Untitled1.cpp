#include <iostream>
#include <string>

using namespace std;

class Superhero {

	unsigned int superheroID, power_rating;
    string hero_name, power_name, origin_universe, hero_alignment; 
    friend class HeroEnsemble;
    
    // TODO (PART A) Fill in other required member attributes and methods below
    // Members should be declared as public or private as appropriate
	Superhero* left;
	Superhero* right;


public:
    Superhero(): superheroID(0), power_rating(0), hero_name(""),power_name(""),
	origin_universe(""), hero_alignment(""), left(NULL), right(NULL) {}
    Superhero(unsigned int new_superheroID, unsigned int new_rating): superheroID(new_superheroID), power_rating(new_rating)
    ,hero_name(""),power_name(""),origin_universe(""), hero_alignment(""), left(NULL), right(NULL) {}
    Superhero(unsigned int new_superheroID, unsigned int new_rating, string new_hero_name,
                string hero_power, string new_origin_universe, string new_hero_alignment): superheroID(new_superheroID), power_rating(new_rating)
    ,hero_name(new_hero_name),power_name(hero_power),origin_universe(new_origin_universe), hero_alignment(new_hero_name), left(NULL), right(NULL) {}
    bool operator==(const Superhero& rhs) const;
    bool operator<(const Superhero& rhs) const;
    bool operator>(const Superhero& rhs) const;
    
    
};

class HeroEnsemble {
    // TODO (PART A) Fill in other required member attributes and methods below
    // Members should be declared as public or private as appropriate
Superhero* root;
int size;


public:
    HeroEnsemble(): root(NULL), size(0) {}
    ~HeroEnsemble() {}
    
    int get_size() const;
    void print();
    
    bool insert_new_hero(Superhero new_hero);
    bool remove_hero(unsigned int remove_heroID);
    bool combine_superheroes(unsigned int combine_heroID);
    bool clone_superhero(unsigned int clone_heroID, unsigned int clone_count);
    bool remove_by_universe(string universe_name);
   	void print(Superhero* T);
   	int power(Superhero* T);
};
void HeroEnsemble::print(Superhero* T) {
	
	if(T == NULL)
		return;
		
	cout << "superheroID: " << T->superheroID << endl << "Power rating: " << T->power_rating << endl << "Hero name:" 
	<< T->hero_name << endl << "Power name: " << T->power_name << endl << "Origin universe: " << T->origin_universe << endl 
	<< "Hero alignement: " << T->hero_alignment << endl << endl;
	print(T->left);
	print(T->right); 
}

void HeroEnsemble::print() {	
	print(root);
}

bool HeroEnsemble::insert_new_hero(Superhero new_hero) {
	// TODO (PART B) Insert your code herebool
	
	if(size == 0)
	{
		root = new Superhero(new_hero);
		size++;
		return true;
	}
	
	Superhero** cur = &root;
    
    while (*cur) {
    	// chekc for duplicates; if found, reject them
    	if((*cur)->superheroID == new_hero.superheroID)
			return false;
		// mov elef tif the given key is smaller than cur's key
		if (new_hero.superheroID < (*cur)->superheroID) // point to the location where
			cur = &((*cur)->left);			// *cur's left pointer is stored
		// move right if given key is greater than cur's key
		else
			cur = &((*cur)->right);	
	}
	*cur = new Superhero(new_hero); // assign newhero at the appropriate position
	++size;
	
	return true;
	// using double pointer first point to the root than point to the left or right of that pointer as needed to access.
	
}

bool HeroEnsemble::combine_superheroes(unsigned int combine_heroID) {
	// TODO (PART C) Insert your code here
	if(size==0)
		return false;
		
	Superhero* cur = root;
	while (cur) {
    	// chekc for duplicates; if found, reject them
    	if(cur->superheroID == combine_heroID)
			break;
		// mov elef tif the given key is smaller than cur's key
		if (combine_heroID < cur->superheroID) // point to the location where
			cur = (cur->left);			// *cur's left pointer is stored
		// move right if given key is greater than cur's key
		else
			cur = (cur->right);	
	}
	cur->power_rating = power(cur);
	cur ->left = NULL;
	cur ->right = NULL;
	
}
int HeroEnsemble::power(Superhero* T)
{
	if(T == NULL)
		return 0;
	return (T->power_rating  + power(T->left) + power(T->right));
	
}
void test_scenario1() {
	HeroEnsemble test_ensemble;
	// TODO (PART B) insert a test scenario here
	test_ensemble.insert_new_hero(Superhero(245, 10));
	test_ensemble.insert_new_hero(Superhero(137, 15,"Clever Firebird",
	"Chemistry", "UWaterloo", "Chaotic Awesome"));
	test_ensemble.insert_new_hero(Superhero(200,12)); 
	test_ensemble.insert_new_hero(Superhero(201,12));
	test_ensemble.insert_new_hero(Superhero(202,12));
	test_ensemble.print();	
}

void test_scenario2() {
	HeroEnsemble test_ensemble;
	// TODO (PART C) insert a test scenario here
	cout << "This is test scenario 2" << endl << endl;
	test_ensemble.insert_new_hero(Superhero(245, 10));
	test_ensemble.insert_new_hero(Superhero(137, 15, "Clever Firebird",
							"Chemistry", "UWaterloo", "Chaotic Awesome"));
	test_ensemble.combine_superheroes(245);
	//IT works for "A" test scenario 
		
	test_ensemble.print();	
 }

int main() {
    // invoke the test runners
    test_scenario1();
    test_scenario2();
}
