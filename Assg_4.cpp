#include<iostream>
using namespace std;

class Directory{
    public:
    string name;
    int phoneNum;
    Directory(){
        name = "";
        phoneNum = -1;
    }
    Directory(string name, int phoneNum){
        this->name = name;
        this->phoneNum = phoneNum;
    }
};

class HashTable{
    Directory *table;
    int size, count;
    public:
    HashTable(int size){
        this->count = 0;
        this->size = size;
        table = new Directory[size];
    }

    void insertWithoutReplacement(string name, int phoneNum){
        int comp = 0;
        bool flag = 0;
        if(count >= size){
            cout<<"Table is full."<<endl;
            return;
        }
        int index = phoneNum % size;
        if(table[index].phoneNum == -1){
            table[index] = Directory(name, phoneNum);
            flag = 1;
            count++;
        }
        else{
            int i = 0;
            while(i <= size){
                comp++;
                if(table[(index + i) % size].phoneNum == -1){
                    table[(index + i) % size] = Directory(name, phoneNum);
                    count++;
                    flag = 1;
                    break;
                }
                i++;
            }
        }
        if(flag){
            cout<<"Inserted using without replacement in "<<comp<<" collisions"<<endl;
        }
    }

    void insertWithReplacement(string name, int phoneNum){
        int comp = 0;
        bool flag = 0;
        if(count >= size){
            cout<<"Table is full."<<endl;
            
            return;
        }
        int index = phoneNum % size;
        if(table[index].phoneNum == -1){
            table[index] = Directory(name, phoneNum);
            count++;
            flag = 1;
        }
        else{
            int i = 0;
            if(table[index].phoneNum % size != index){
                swap(table[index].name, name);
                swap(table[index].phoneNum, phoneNum);
            }
            while(i <= size){
                comp++;
                if((table[(index + i) % size].phoneNum == -1)){
                    // table[(index + i) % size] = Directory(name, phoneNum);
                    table[(index + i) % size] = Directory(name, phoneNum);
                    count++;
                    flag = 1;
                    break;
                }
                i++;
            }
        }
        if(flag){
            cout<<"Inserted using with replacement in "<<comp<<" collisions"<<endl;
        }
    }

    
    void search(int phoneNum){
        int comp = 0;
        bool flag = 0;
        int index = phoneNum % size;
        if(table[index].phoneNum == phoneNum){
            comp++;
            flag = 1;
            cout<<table[index].name<<endl;
        }
        else{
            int i = 0;
            while(i <= size){
                comp++;
                if(table[(index + i) % size].phoneNum == phoneNum){
                    cout<<table[(index + i) % size].name<<endl;
                    flag = 1;
                    break;
                }
                i++;
            }
        }
        if(flag){
            cout<<"Found in "<<comp<<" comparisons"<<endl;
        }else{
            cout<<"Not Found";
        }
    }

    void display(){
        cout<<"Key    Name       Phone-Number"<<endl;
        for(int i = 0; i < size; i++){
            if(table[i].phoneNum == -1) cout<<i<<"    ------------------"<<endl;
            else cout<<i<<"    "<<table[i].name<<"    "<<table[i].phoneNum<<endl;
        }
    }
    
};

void inputSequence(HashTable& obj1, HashTable& obj2){
    while(true){
        string name;
        int phoneNum;
        cout<<"\nEnter Name to store: ";
        cin>>name;
        cout<<"\nEnter Phone Number to store: ";
        cin>>phoneNum;
        if(phoneNum == -1) break;
        obj1.insertWithoutReplacement(name, phoneNum);
        obj2.insertWithReplacement(name, phoneNum);
    }
}

int main(){
    HashTable obj1(10);
    HashTable obj2(10);
    int k;
    while(k != -1){
        cout<<"\n1. Insert in HashTable.\n2. Search in Table\n";
        cout<<"3. Display the Table:  ";
        cin>>k;
        switch (k)
        {
        case 1:
            inputSequence(obj1, obj2);
			break;
		case 2:
            int phone;
            cout<<"\nEnter the number to search: ";
            cin>>phone;
            obj1.search(phone);
            obj2.search(phone);
			break;
		case 3:
            obj1.display();
            cout<<endl;
            obj2.display();
			break;
		
		// case 4:
        //     cout<<"\nEnter element to delete: ";
        //     int key;
        //     cin>>key;
        //     obj.deleteNodeInBST(obj.root, key);
        //     cout<<"After deletion: ";
        //     obj.inorder();
		// 	break;
        
        default:
            break;
        }
    }
   return 0;
}