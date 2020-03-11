#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace::std;
ofstream fout;
ifstream fin;

void menu();


class encrypt
 {
   string seed,key[4],filename,encrypted_filename;

      public:

      void get_seed()
      {
        cout<<" Enter Password: ";getline(cin,seed);
        cin.get();
      }

      void get_filename()
       {
        cout<<"\n Enter Filename(File should be stored in the bin folder and should be a text file only): ";
        cin.ignore();
        getline(cin,filename);

        encrypted_filename=filename+"_encrypted.txt";

        filename=filename+".txt";
        cin.get();
       }

      void set_key()
       {
         key[0]=seed;
         key[1]=seed;
         key[2]="";
         key[3]="";
         char temp;

         for (int i=0,j=seed.size()-1; i<seed.size()/2; i++,j--)
          {
            temp=key[1][i];
            key[1][i]=key[0][j];
            key[1][j]=temp;
          }

         for (int i=0; i<seed.size(); i++)
          key[2]=key[2]+(char(key[0][i]&key[1][i]));

         for (int i=0; i<seed.size(); i++)
          key[3]=key[3]+char(seed[i]+seed.size());
       }


       void lock()
       {
         const char * c = filename.c_str();

         fin.open(filename,ios::in);
         fout.open("temp.txt",ios::out);
         string temp;
         int j=0,ptr=0;

        if (!fin)
         {
           system("CLS");
           cout<<"\nNo such File Exists...\n";
           cin.get();
           exit(0);
         }

        while (!fin.eof())
        {
             getline(fin,temp);


          for (int i=0; i<temp.size(); i++)
           {
            if (temp[i]==' ')
             fout<<'!';


            else
            {
             fout<<(temp[i]^key[ptr][j]);

             if (j==seed.size()-1)
             {
               j=0;

               if (ptr==3)
                ptr=0;

              else
               ptr++;
             }
             else
              j++;
            }

            fout<<' ';
          }

          fout<<"$ ";
       }

         system("CLS");
         cout<<"\n Process Successful..";
         cout<<"\n File encrypted and saved as "<<encrypted_filename<<endl;
         cout<<"\n Please remember your Password for future decryption.";
         cout<<"\n\nThank You for using the Encrypter Program.....";
         cout<<"\n\n\nPlease Exit to Main Menu by pressing Enter....";
         cin.get();
        



       fin.close();
       fout.close();

        const char * new_filename = encrypted_filename.c_str();

          remove(c);
          rename("temp.txt",new_filename);
       }

      void unlock()
       {
         fin.open(encrypted_filename,ios::in);
         fout.open(filename,ios::out);

         string temp;
         int i=0,ptr=0;

         while (!fin.eof())
          {
            fin>>temp;

            if (temp=="!")
             fout<<" ";

            else if (temp=="$")
             fout<<"\n";

            else
            {
             char a=stoi(temp);
             fout<<char(a^key[ptr][i]);

             if (i==seed.size()-1)
             {
               i=0;

               if (ptr==3)
                ptr=0;

               else
                ptr++;
             }
             else
              i++;
            }
        }

         system("CLS");
         cout<<"\n Process Successful..";
         cout<<"\n File De-encrypted and saved as "<<filename<<endl;
         cout<<"\n\nThank You for using the Encrypter Program.....";
         cout<<"\n\n\nPlease Exit to Main Menu for accessing the De-encrypted File by pressing Enter....";
         cin.get();


         fin.close();
         fout.close();

         const char * new_filename = filename.c_str();
         const char * c = encrypted_filename.c_str();

        remove(c);
        rename(c,new_filename);

    }

  void get_details()
   {
     get_filename();
     get_seed();
   }

 }e;



int main()
 {
  menu();
  return 0;
 }



void menu()
 {
  int choice;
  system("CLS");

  cout<<"\n 1) Lock";
  cout<<"\n 2) Unlock";
  cout<<"\n 3) Exit";

  cout<<"\n\n Enter Your Choice: ";cin>>choice;

  switch(choice)
   {
    case 1: e.get_details();
            e.lock();
            cin.get();
            menu();


    case 2: cout<<"\n Enter your original filename (No need to enter as file_encrypted) ";
            e.get_details();
            e.unlock();
            cin.get();
            menu();

    case 3: exit(0);

    default: cout<<"Invalid Choice...";
             cin.get();
             menu();
   }
 }