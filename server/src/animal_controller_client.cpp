#include "file_animal.cpp"

/*
 * Refers to read animal from disk
 */
inline animal read_animal(int pos){
    animal a = read_file(pos);
    return a;
}
/*
 * Write animla in disk
 */
inline int write_animal(animal a){
    int pos = get_code();//Get the position in disk to storage the animal
    write_file(a, pos);   
  // read_animal(pos);
  return pos;
}

/*
 * Write animal in disk but in custom location
 */
inline int write_animal(animal a, int pos){
    write_file(a, pos);   
    return pos;
}

/*
 * Operation for the user for create an animal from memory to disk
 */
inline void insert_animal(animal a1 ){

    //Getting the hash number of the animal
    ll hash = get_hash(a1.name);
        
    //Persisting the animal and getting the location in disk
    ll location_disk = write_animal(a1);

    //Save location in hash table
    data[hash].push_back(location_disk);
    cout << "The register has been inserted succesfully" << endl;

}

/*
 * User operation for show the animal
 */

inline void show_animal(){
    ll total = 0;
    int number_register;
    cout << "\n SHOW REGISTER \n";
    for(int i=0; i< size_hash_table; i++){
        total += data[i].size();
    }
    cout << " Total number of registers is: " << (total-1);
    cout << " User write the number of the register to see, please" << endl;
    cout << " Number of the register = " ;
    
    cin >> number_register;

    if (exist(number_register) && number_register <= (total-1)){        //First Check in RAM
        animal aux = read_animal(number_register);   //SECOND ACCESS TO DISK
        show_animal(aux);
    }else{
        cout << "\nUser that number is not register in the database\n";
    }

    
}
    

/*
 * Delete animal
 */
inline void delete_animal(){

    //show_hash_table();
    int number_register;
    cout << "\n DELETE REGISTER \n";
    
    
    cout << " Number of the register = " ;
    
    cin >> number_register;
  
    if (exist(number_register)){      //Exist?  
       // show_hash_table();
        delete_item(number_register); //First delete from memory
        
        //Now interchange move the last position to this location
        //It is important remark that number_register is the location in memory
        int greatest =  change_greatest_location(number_register);
        cout << endl;

        //Change this locations 
        //Get the animal in the greatest location: The end of the file
        animal aux = read_animal(greatest);
        //Write the last animal in the location that was  erase in hash table
        delete_file(aux,number_register);


        
        
    //    show_hash_table();
    }else{
        cout << "\nUser that number is not registered in the database\n";
    }
    

}

/*
 * Show animals with an specific name
 */
inline void show_animal_r(){
    string name;
    cout << "\n SHOW ANIMALS BY NAME\n";
    
    
    cout << " Name of the register = " ; cin >> name;
    int hash = get_hash (name);
    cout << " The hash of " << name << " is: " << hash << endl;

    vi values = get_locations(hash);
    cout << endl <<"Number of positions in disk with the same hash: " << values.size() << endl;

    show_row_table(hash);

    cout << endl << "Animals that has the same hash :" << endl;

    for (int i= 0; i< values.size(); i++){
        
        animal aux = read_animal(values[i]);
        string name_a(aux.name);
        //This line transform to lower case the name
        transform(name_a.begin(), name_a.end(), name_a.begin(), ::tolower);
        transform(name.begin(), name.end(), name.begin(), ::tolower);


        if (name.compare(name_a) == 0){
            cout << "#" << i << endl;
            show_animal(aux);
            cout << endl;
        }
    }
    cout << endl;
    
}


