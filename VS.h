#include<iostream>
#include<string.h>
#include<fstream>
#include<iomanip>
#include<windows.h>
using namespace std;

//forward declaration
void loading();
void admin();
void cases();
void menu();
void generate_result();
void display_individual_votes();
void display_list();
void start_voting();
void Add_members_in_queue();
void dequeue_node();
void enqueue_node();
void print(string arr[], int n);
void mergesort(string arr[], int l, int r);
void merge(string arr[], int l, int mid, int r);
int search (string x);

//global variables and arrays
static int p=0;//variable for cnic array
static int count_node=0;//to count nodes
static int A=0;//viriable of X candidate array
static int B=0;//variable of Y candidate array
static int C=0;//variable of C candidate array
static int voterX = 0;//counter variable for counting votes of candidate X.
static int voterY = 0;//counter variable for counting votes of candidate Y.
static int voterZ = 0;//counter variable for counting votes of candidate Z.
const string PASS="1234";// admin login password
const int Max=100;//maximum declaration
string cnics[Max];//array used for linear search that if a same cnic person is voting for 2nd time or not.
string name_arr[Max];// used to sort names throught merge sort.

void loading()
{
	system("color 0B");//system color
	char a=219;//this is the symbol of box 
	cout<<"\n\n\n\n\n\n\n\n\t\t\t\t\tSYSTEM IS STARTING PLEASE WAIT......\n\n\t\t\t\t\t";
	for(int i=0;i<35;i++)//simple loop 
	{
		cout<<a;//displaying bar
		Sleep(35);//this is the variable that shows the speed of box moving left to right
	}
	cout<<endl;
	system("cls");
}

struct node {
	string cnic;
	string name;
	string place;
	string gender;
	node *next;
	node *prev;
};
node *front=NULL;
node *rear=NULL;


int search (string x) {

	int flag=0;
	if(p>0) {
		for(int i=0; i<p; i++) {
			if(x==cnics[i]) {
				flag=1;
			}

		}

	}
	return flag;
}

void merge(string arr[], int l, int mid, int r){
	
	int n1 = mid - l + 1;
	int n2 = r - mid;
	
	string a[n1];
	string b[n2];
	
	for(int i=0;i<n1;i++){
		a[i] = arr[l+i];
	}
	
	for(int i=0;i<n2;i++){
		b[i] = arr[mid+i+1];
	}
	
	int i = 0;
	int j = 0;
	int k = l;
	
	while(i<n1 && j<n2){
		if(a[i]<b[j]){
			arr[k] = a[i];
			k++; i++;
		}
		else{
			arr[k] = b[j];
			k++; j++;
		}
	}
	
	while(i<n1){
		arr[k] = a[i];
		k++; i++;
	}
	
	while(j<n2){
		arr[k] = b[j];
		k++; j++;
	}
}

void mergesort(string arr[], int l, int r){
	
	if(l<r){
	
		int mid = (l+ r) / 2;
		
		mergesort(arr, l, mid);
		mergesort(arr, mid+1, r);
		
		merge(arr, l, mid, r);
	}
}

void print(string arr[], int n){
	for(int i=0;i<=n;i++){
		cout<<arr[i]<<endl;
	}
}


void enqueue_node() {

	node *newnode=new node;
	newnode->next=NULL;
	newnode->prev=NULL;

	cout<<"Enter your Cnic : ";
	cin>>newnode->cnic;
	if(search(newnode->cnic)==1) {
		cout<<"You have already voted "<<endl;
	} else {
		cout<<"Enter your name : ";
		cin>>newnode->name;
		name_arr[count_node]=newnode->name;
		cout<<"Enter you gender : ";
		cin>>newnode->gender;
		cout<<"Enter your birth place : ";
		cin>>newnode->place;
		cnics[p]=newnode->cnic;
		p++;
		fstream mf;
		mf.open("Complete Data Store.txt",ios_base::app);
		mf<<newnode->name<<" "<<newnode->cnic<<" "<<newnode->gender<<" "<<newnode->place<<endl;
		mf.close();


		if(front==NULL) {

			front=newnode;
			rear=newnode;
			count_node++;
		} else {

			rear->next=newnode;
			newnode->prev=rear;
			rear=newnode;
			count_node++;
		}

	}
}


void dequeue_node() {
	if(front == NULL) {
		cout<<"Queue is empty\n";
	} else {
		node *temp=front;
		front = front->next;
		if(front!= NULL)
		{
			front->prev = NULL;
		}
		else
		{
			front = rear = NULL;
			cout<<"Queue is empty now\n";
		}
		delete temp;
	}
}

void Add_members_in_queue() {
	int flag=1;
	while(flag==1) {
		enqueue_node();
		cout<<"Do u want to Add more members? \nIf yes Press 1 ";
		cin>>flag;
	}
}



void start_voting() {
	string arr1[Max],arr2[Max],arr3[Max];
	string option;

	fstream mf;
	while(front != NULL) {
		cout<<"Turn of "<<front->cnic<<" :"<<endl;
		cout<<"Who do u want to vote: "<<endl;
		cout<<"1.X"<<endl;
		cout<<"2.Y"<<endl;
		cout<<"3.Z"<<endl;
		cin>>option;
		if(option=="1") {
			arr1[A]=front->cnic;
			fstream mf;
			mf.open("X.txt",ios_base::app);
			mf<<front->cnic<<endl;
			mf.close();
			A++;
			voterX++;
			dequeue_node();

		} else if(option=="2"){
			arr2[B]=front->cnic;
			mf.open("Y.txt",ios_base::app);
			mf<<front->cnic<<endl;
			mf.close();
			B++;
			voterY++;
			dequeue_node();

		} else if(option=="3") {
			arr3[C]=front->cnic;
			mf.open("Z.txt",ios_base::app);
			mf<<front->cnic<<endl;
			mf.close();
			C++;
			voterZ++;
			dequeue_node();

		} else {
			cout<<"Wrong input \n";
		}


	}
}

void display_list() {
	node *temp=new node;
	fstream mf;
	int totalVoters = 0;
	mf.open("Complete Data Store.txt",ios_base::in);
	cout<<"                                  VOTER'S LIST";
	cout<<"\n------------------------------------------------------------------------------------------\n";
	cout<<"   NAME \t CNIC \t GENDER  \t PLACE  \n";
	cout<<"------------------------------------------------------------------------------------------\n";
	while(mf.peek()!= EOF) {
		mf>>temp->name>>temp->cnic>>temp->gender>>temp->place;
		mf.ignore(); //ignore newline character\n
		cout<<endl<<temp->name<<setw(12)<<temp->cnic<<setw(12)<<temp->gender<<setw(12)<<temp->place;
		totalVoters++;
	}
	mf.close();
	cout<<"\nTotal voters are : "<<totalVoters<<endl;
	cout<<"------------------------------------------------------------------------------------------";
	delete temp;
}


void display_individual_votes() {
	node *temp=new node;
	
	int input,flag=1;

	while(flag==1) {
		cout<<"Which candidate data u want to display? \n1.X\n2.Y\n3.Z ";
		cin>>input;
		if(input==1) {
			fstream mf;
			mf.open("X.txt",ios_base::in);
			cout<<"\n-----------------------------------------------------\n";
			cout<<"        CNIC   \n";
			cout<<"--------------------------------------------------------\n";
			while(mf.peek()!= EOF) {
				mf>>temp->cnic;
				cout<<temp->cnic<<endl;
				flag=0;
				mf.ignore();
			}
			mf.close();
			cout<<"\n---------------------------------------------------------\n";
			cout<<"Total voters of X are : "<<voterX<<endl;

		} else if(input==2) {
			fstream mf;
			mf.open("Y.txt",ios_base::in);
			cout<<"\n-----------------------------------------------------\n";
			cout<<"        CNIC   \n";
			cout<<"--------------------------------------------------------\n";
			while(mf.peek()!= EOF) {
				mf>>temp->cnic;
				cout<<temp->cnic<<endl;
				mf.ignore();
				flag=0;
			}
			mf.close();
			cout<<"\n---------------------------------------------------------\n";
			cout<<"Total voters of Y are : "<<voterY<<endl;

		} else if(input==3) {
			fstream mf;
			mf.open("Z.txt",ios_base::in);
			cout<<"\n-----------------------------------------------------\n";
			cout<<"        CNIC   \n";
			cout<<"--------------------------------------------------------\n";
			while(mf.peek()!= EOF) {
				mf>>temp->cnic;
				cout<<temp->cnic<<endl;
				mf.ignore();
				flag=0;
			}
			mf.close();
			cout<<"\n---------------------------------------------------------\n";
			cout<<"Total voters of Z are : "<<voterZ<<endl;
		} else {
			cout<<"Wrong input"<<endl;
			cout<<"Enter Valid Input: ";
			cin>>flag;
		}
		cout<<"do you want to check further results?\nif yes press 1 "<<endl;
		cin>>flag;
	}
	delete temp;
}


void generate_result()
{
	if(voterX>voterY&&voterX>voterZ)
	{
		cout<<"Candidate X is the winner\nWith "<<voterX<<" votes"<<endl;
		cout<<"Votes of Y are "<<voterY<<" \nVotes of Z are "<<voterZ<<endl;
	}
	else if(voterY>voterX&&voterY>voterZ)
	{
		cout<<"Candidate Y is the winner\nWith "<<voterY<<" votes"<<endl;
		cout<<"Votes of X are "<<voterX<<" \nVotes of Z are "<<voterZ<<endl;
	}
	else if(voterZ>voterX&&voterZ>voterY)
	{
		cout<<"Candidate Z is the winner\nWith "<<voterZ<<" votes"<<endl;
		cout<<"Votes of X are "<<voterX<<" \nVotes of Y are "<<voterY<<endl;
	}
	else if(voterX>voterZ && voterY>voterZ && voterX==voterY){
		cout<<"X and Y got equal votes"<<endl;
		cout<<"X votes are :"<<voterX<<"\nY votes are : "<<voterY<<"\nZ votes are : "<<voterZ;
		cout<<"Result : X and Y are winner "<<endl;
	}
	else if(voterX>voterY && voterZ>voterY && voterX==voterZ){
		cout<<"X and Z got equal votes"<<endl;
		cout<<"X votes are :"<<voterX<<"\nZ votes are : "<<voterZ<<"\nY votes are : "<<voterY;
		cout<<"Result : X and Z are winner "<<endl;
	}
	else if(voterY>voterX && voterZ>voterX && voterZ==voterY){
		cout<<"Y and Z got equal votes"<<endl;
		cout<<"Y votes are :"<<voterY<<"\nZ votes are : "<<voterZ<<"\nX votes are : "<<voterX;
		cout<<"Result : Y and Z are winner"<<endl;
	}
	else if(voterX==0 &&voterY==0 && voterZ==0){
		cout<<"No one has voted the candidates from the time programm has started again :)"<<endl;
	}
	else if(voterX==voterY&& voterX==voterZ ){
		cout<<"X , Y and Z got equal votes"<<endl;
		cout<<"X votes are :"<<voterX<<"\nY votes are : "<<voterY<<"\nZ votes are : "<<voterZ;
		cout<<"\nResult : No one is winner";
	}
	else 
	{
		cout<<"\nNO voters have been vote "<<endl;
	}
}
void menu() {

cout<<"===================================\n";
cout<<"|Select Option                     |"<<endl;
cout<<"|1.Add members in queue            |"<<endl;
cout<<"|2.Start Voting                    |"<<endl;
cout<<"|3.Admin                           |"<<endl;
cout<<"|0 To exit                         |"<<endl;
cout<<"===================================\n";
}

void cases() {

	int opt;
	cout<<"=========================\n";
	  cout<<" Enter your Option >>   ";
	  cin>>opt;                    
	cout<<"=========================\n";
	switch(opt) {

		case 1:
			Add_members_in_queue();
			int num;
			cout<<"\npress 0 to go back: ";
			cin>>num;
			if(num==0) {
				system("cls");
				menu();
				cases();
			}
			break;

		case 2:
			start_voting();
			int num2;
			cout<<"\npress 0 to go back: ";
			cin>>num2;
			if(num2==0) {
				system("cls");
				menu();
				cases();
			}
			break;
		case 3:
				admin();
				system("cls");
				menu();
				cases();
			break;
		case 0:
			break;

		default:
			cout<<"Sorry :(";
			cout<<"\nU have to choose from 1 to 4"<<endl;

			system("cls");
	}
}

void admin() {
	int cont=1,cont2=1,choice;
	string pass,opt;
	while(cont==1) {

		cout<<"Enter Admin Password : ";
		cin>>pass;

		if(pass==PASS) {

			while(cont2==1) {
				cout<<"What do you want to perform ?"<<endl;
				cout<<"===========================================================================================================\n";
				cout<<"\n1.Check voted people list\n2.Check individual person votes\n3.Display Sorted names\n4.Generate Result\n0.Go back >>";
				cin>>choice;
				cout<<"===========================================================================================================\n";
				if(choice==1) {
					display_list();

				} else if(choice==2) {
					display_individual_votes();

				}
				else if(choice==3)
				{
					mergesort(name_arr,0,count_node);
					print(name_arr, count_node);
				 } 
				 else if(choice==4)
				 {
				 	generate_result();
				 }
				 else if(choice ==0){
				 	break;
				 }
				 else {
					cout<<"wrong input\nEnter choice again"<<endl;
					cin>>choice;
					break;
					
				
				}
				
				cout<<"\nDo you want do continue as admin?\n1 for yes\nPress  2 for no"<<endl;
				cin>>cont2;
				if(cont2==2){
					break;
				}
			}
			cont=0;//admin close
		}
		else {
			cout<<"Sorry the password is incorrrect "<<endl;
			cout<<"do you want to continue?\npress 1 for yes\npress any key for no\n"<<endl;
			cin>>opt;
			if(opt=="1"){
				cont=1;
			}
			else{
				break;
			}
			
		}
	}
}
