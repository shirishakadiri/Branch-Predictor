#include <iostream>
#include <fstream>
//#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <stack>
using namespace std;

vector<int> predictionTableHybridGshare;
vector<int> predictionTableHybridBimodal;
vector<int> chooserTableHybrid;
string gbhrHybrid;
double noOfMisPreHybrid = 0;
vector<int> predictionTableGshare;
string gbhr;
double noOfMisPreGshare = 0;
vector<int> predictionTableBimodal;
double noOfMisPreBimodal = 0;


string HexToBin(string hexdec)
{
    long int i = 0;
    string binaryNumber = "";
    
    while (hexdec[i]) {
        
        switch (hexdec[i]) {
            case '0':
                binaryNumber.append("0000");
                break;
            case '1':
                binaryNumber.append("0001");
                break;
            case '2':
                binaryNumber.append("0010");
                break;
            case '3':
                binaryNumber.append("0011");
                break;
            case '4':
                binaryNumber.append("0100");
                break;
            case '5':
                binaryNumber.append("0101");
                break;
            case '6':
                binaryNumber.append("0110");
                break;
            case '7':
                binaryNumber.append("0111");
                break;
            case '8':
                binaryNumber.append("1000");
                break;
            case '9':
                binaryNumber.append("1001");
                break;
            case 'A':
            case 'a':
                binaryNumber.append("1010");
                break;
            case 'B':
            case 'b':
                binaryNumber.append("1011");
                break;
            case 'C':
            case 'c':
                binaryNumber.append("1100");
                break;
            case 'D':
            case 'd':
                binaryNumber.append("1101");
                break;
            case 'E':
            case 'e':
                binaryNumber.append("1110");
                break;
            case 'F':
            case 'f':
                binaryNumber.append("1111");
                break;
            default:
                cout << "\nInvalid hexadecimal digit "<< hexdec[i];
        }
        i++;
    }
    //cout << binaryNumber << endl;
    return binaryNumber;
}

int binaryStringToDecimal(string n)
{
    string num = n;
    int dec_value = 0, base = 1, len = num.length();
    for (int i=len-1;i>=0;i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    return dec_value;
}

int binaryIntToDecimal(int n)
{
    int num = n,dec_value = 0,base = 1,temp = num;
    while (temp)
    {
        int last_digit = temp % 10;
        temp = temp/10;
        dec_value += last_digit*base;
        base = base*2;
    }
    return dec_value;
}

int decToBinary(int n)
{
    int binaryNumber = 0;
    int remainder, i = 1, step = 1;
    if(n == 3){
        return 11;
    }
    else{
        while (n!=0)
        {
            remainder = n%2;
            
            n /= 2;
            binaryNumber += remainder*i;
            i *= 10;
        }
        return binaryNumber;
    }
    //cout<< binaryNumber;
    
}

string myXOR(string x, string gbhrHybrid, int n)
{
    string res = "";
    for (int i = 0; i < n; i++ ){
        if(x[i] == gbhrHybrid[i]){
            res.append("0");
        }
        else{
            res.append("1");
        }
    }
    return res;
}

int bimodalPredictionHybrid(int decimalNumber, string takenOrNot , int checkDecimal)
{
    //int checkBinary = predictionTableGshare.at(decimalNumber);
    //int checkDecimal = binaryIntToDecimal(checkBinary);
    int result;
    //cout << decimalNumber << " : " << checkDecimal << " : " << checkBinary <<endl;
    if(checkDecimal >= 4){
        //cout << "Prediction:\t" << "true" <<endl;
        if((takenOrNot == "t") && (checkDecimal < 7)){
            checkDecimal = checkDecimal + 1;
            result = 1;
        }
        else if((takenOrNot == "n") && (checkDecimal > 0)){
            checkDecimal = checkDecimal - 1;
            result = 0;
        }
    }
    else{
        //cout << "Prediction:\t" << "false" <<endl;
        if((takenOrNot == "t") && (checkDecimal < 7)){
            checkDecimal = checkDecimal + 1;
            result = 0;
        }
        else if((takenOrNot == "n") && (checkDecimal > 0)){
            checkDecimal = checkDecimal - 1;
            result = 1;
        }
    }
    
    //cout << checkDecimal<<endl;
    int updateCheck = decToBinary(checkDecimal);
    //cout << "New bimodal-PT value:\t" << checkDecimal <<endl;
    predictionTableHybridBimodal.at(decimalNumber) = updateCheck;
    return result;
    //cout << "new-" << predictionTable.at(decimalNumber-1) << endl;
}

void bimodalPrediction(int decimalNumber, string takenOrNot)
{
    int checkBinary = predictionTableBimodal.at(decimalNumber);
    int checkDecimal = binaryIntToDecimal(checkBinary);
    //cout << "PT value:\t" << checkDecimal <<endl;
    
    if(checkDecimal >= 4){
        //cout << "Prediction:\t" << "true" <<endl;
        if((takenOrNot == "t") && (checkDecimal < 7)){
            checkDecimal++;
        }
        else if((takenOrNot == "n") && (checkDecimal > 0)){
            checkDecimal--;
            noOfMisPreBimodal++;
        }
    }
    else{
        //cout << "Prediction:\t" << "false" <<endl;
        if((takenOrNot == "t") && (checkDecimal < 7)){
            checkDecimal++;
            noOfMisPreBimodal++;
        }
        else if((takenOrNot == "n") && (checkDecimal > 0)){
            checkDecimal--;
        }
    }
    
    int updateCheck = decToBinary(checkDecimal);
    //cout << "New PT value:\t" << checkDecimal <<endl;
    predictionTableBimodal.at(decimalNumber) = updateCheck;
    //cout << "new-" << predictionTable.at(decimalNumber-1) << endl;
}

void gsharePrediction(int decimalNumber, string takenOrNot)
{
    int checkBinary = predictionTableGshare.at(decimalNumber);
    int checkDecimal = binaryIntToDecimal(checkBinary);
    //cout << "PT value:\t" << checkDecimal <<endl;
    
    if(checkDecimal >= 4){
        //cout << "Prediction:\t" << "true" <<endl;
        if((takenOrNot == "t") && (checkDecimal < 7)){
            checkDecimal++;
        }
        else if((takenOrNot == "n") && (checkDecimal > 0)){
            checkDecimal--;
            noOfMisPreGshare++;
        }
    }
    else{
        //cout << "Prediction:\t" << "false" <<endl;
        if((takenOrNot == "t") && (checkDecimal < 7)){
            checkDecimal++;
            noOfMisPreGshare++;
        }
        else if((takenOrNot == "n") && (checkDecimal > 0)){
            checkDecimal--;
        }
    }
    //cout << checkDecimal<<endl;
    int updateCheck = decToBinary(checkDecimal);
    //cout << "New PT value:\t" << checkDecimal <<endl;
    
    predictionTableGshare.at(decimalNumber) = updateCheck;
    //cout << "new-" << predictionTable.at(decimalNumber-1) << endl;
}

int gsharePredictionHybrid(int decimalNumber, string takenOrNot, int checkDecimal)
{
    //int checkBinary = predictionTableGshare.at(decimalNumber);
    //int checkDecimal = binaryIntToDecimal(checkBinary);
    int result;
    
    //if taken
    if(checkDecimal >= 4){
        //cout << "Prediction:\t" << "true" <<endl;
        if((takenOrNot == "t") && (checkDecimal < 7)){
            checkDecimal = checkDecimal + 1;
            result = 1;
        }
        else if((takenOrNot == "n") && (checkDecimal > 0)){
            checkDecimal = checkDecimal - 1;
            result = 0;
        }
    }
    else{
        //cout << "Prediction:\t" << "false" <<endl;
        if((takenOrNot == "t") && (checkDecimal < 7)){
            checkDecimal = checkDecimal + 1;
            result = 0;
        }
        else if((takenOrNot == "n") && (checkDecimal > 0)){
            checkDecimal = checkDecimal - 1;
            result = 1;
        }
    }
    //cout << checkDecimal<<endl;
    int updateCheck = decToBinary(checkDecimal);
    //cout << "New gshare-PT value:\t" << checkDecimal <<endl;
    predictionTableHybridGshare.at(decimalNumber) = updateCheck;
    return result;
    //cout << "new-" << predictionTable.at(decimalNumber-1) << endl;
}

void hybridFlow(int k, int m1, int n, int m2, string fileName){
    int startIndex = 0;
    int endIndex = 0;
    
    ifstream file;
    string line;
    /*
     k = atoi(argv[2]);
     m1 = atoi(argv[3]);
     n = atoi(argv[4]);
     m2 = atoi(argv[5]);
     string fileName = argv[6];
     */
    //create global branch history register
    for(int i=0 ; i<n ; i++){
        gbhrHybrid.append("0");
    }
    
    //create PT for gshare
    int base = 2,exponent = m1,s,noOfEntryGshare=1;
    for( s=exponent ; s>0 ; s--)
    {
        noOfEntryGshare = noOfEntryGshare * base;
    }
    int j=0;
    while(j < noOfEntryGshare) {
        predictionTableHybridGshare.push_back(100);
        j++;
    }
    
    //create PT for bimodal
    base = 2,exponent = m2;
    int noOfEntryBimodal=1;
    for( s=exponent ; s>0 ; s--)
    {
        noOfEntryBimodal = noOfEntryBimodal * base;
    }
    j=0;
    while(j < noOfEntryBimodal) {
        predictionTableHybridBimodal.push_back(100);
        j++;
    }
    
    //create chooser table for hybrid
    base = 2,exponent = k;
    int noOfEntryhybrid=1;
    for( s=exponent ; s>0 ; s--)
    {
        noOfEntryhybrid = noOfEntryhybrid * base;
    }
    j=0;
    while(j < noOfEntryhybrid) {
        chooserTableHybrid.push_back(01);
        j++;
    }
    
    //Run for every line
    file.open(fileName);
    int i = 0;
    getline(file, line);
    while(!file.eof()){
        
        //cout << "<line "  << " #" << i << ">\t" << line <<endl;
        istringstream ss(line);
        string binaryString = "";
        int decimalNumber = 0;
        int binaryNumber = 0;
        string word;
        ss >> word;
        
        //get hexadecimal and taken/nottaken value
        vector <string> tokens;
        stringstream check1(line);
        string intermediate;
        while(getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }
        string takenOrNot = tokens[1];
        binaryString = HexToBin(word);
        
        
        //----------------------------------------------------------------
        //BIMODAL PREDICTION
        startIndex = binaryString.length() - (m2+2);
        endIndex = m2;
        
        string bimodalIndex = binaryString.substr(startIndex, endIndex);
        
        
        //-----------------------------------------------------------------
        //GSHARE
        startIndex = binaryString.length() - (n+2);
        endIndex = n;
        string xorPCBits = binaryString.substr(startIndex,endIndex);
        string xorResult = myXOR(xorPCBits, gbhrHybrid,n);
        
        startIndex = binaryString.length() - (m1+2);
        endIndex = m1 - n;
        
        string gshareIndex = binaryString.substr(startIndex, endIndex);
        gshareIndex.append(xorResult);
        
        
        //-----------------------------------------------------------------
        //HYBRID PREDICTION
        startIndex = binaryString.length() - (k+2);
        endIndex = k;
        
        string chooserTableIndex = binaryString.substr(startIndex,endIndex);
        int CTIndex = binaryStringToDecimal(chooserTableIndex);
        
        //CT values
        //cout << "CT index:\t" << CTIndex << endl;
        int checkBinaryHybrid = chooserTableHybrid.at(CTIndex);
        int checkDecimalHybrid = binaryIntToDecimal(checkBinaryHybrid);
        //cout << "CT value:\t" << checkDecimalHybrid <<endl;
        
        //bimodal values
        int bPTIndex = binaryStringToDecimal(bimodalIndex);
        //cout << "bimodal-PT index:\t" << bPTIndex << endl;
        int checkBinaryBimodal = predictionTableHybridBimodal.at(bPTIndex);
        int checkDecimalBimodal = binaryIntToDecimal(checkBinaryBimodal);
        //cout << "bimodal-PT value:\t" << checkDecimalBimodal <<endl;
        
        //gshare values
        int gPTIndex = binaryStringToDecimal(gshareIndex);
        //cout << "gshare-PT index:\t" << gPTIndex << endl;
        int checkBinaryGshare = predictionTableHybridGshare.at(gPTIndex);
        int checkDecimalGshare = binaryIntToDecimal(checkBinaryGshare);
        //cout << "gshare-PT value:\t" << checkDecimalGshare <<endl;
        
        //select the prediction method
        
        //Bimodal prediction for chooser input
        int chooserInputBimodal = 0;
        if(checkDecimalBimodal >= 4){
            //cout << "Prediction:\t" << "true" <<endl;
            if(takenOrNot == "t"){
                //checkDecimal = checkDecimal + 1;
                chooserInputBimodal = 1;
            }
            else if(takenOrNot == "n"){
                //checkDecimal = checkDecimal - 1;
                chooserInputBimodal = 0;
            }
        }
        else{
            //cout << "Prediction:\t" << "false" <<endl;
            if(takenOrNot == "t"){
                //checkDecimal = checkDecimal + 1;
                chooserInputBimodal = 0;
            }
            else if(takenOrNot == "n"){
                //checkDecimal = checkDecimal - 1;
                chooserInputBimodal = 1;
            }
        }
        
        //Gshare prediction for chooser input
        int chooserInputGshare = 0;
        if(checkDecimalGshare >= 4){
            //cout << "Prediction:\t" << "true" <<endl;
            if(takenOrNot == "t"){
                //checkDecimal = checkDecimal + 1;
                chooserInputGshare = 1;
            }
            else if(takenOrNot == "n"){
                //checkDecimal = checkDecimal - 1;
                chooserInputGshare = 0;
                //noOfMisPreHybrid++;
            }
        }
        else{
            //cout << "Prediction:\t" << "false" <<endl;
            if(takenOrNot == "t"){
                //checkDecimal = checkDecimal + 1;
                chooserInputGshare = 0;
                //noOfMisPreHybrid++;
            }
            else if(takenOrNot == "n"){
                //checkDecimal = checkDecimal - 1;
                chooserInputGshare = 1;
            }
        }
        
        //Chooser table
        int predictOutcome = 0;
        if(checkDecimalHybrid >= 2){
            //GSHARE
            if(checkDecimalGshare >= 4){
                //cout <<"Prediction:\t" <<"true"<<endl;
            }
            else{
                //cout <<"Prediction:\t" <<"false"<<endl;
            }
            predictOutcome = gsharePredictionHybrid(gPTIndex, takenOrNot, checkDecimalGshare);
        }
        else{
            //BIMODAL
            
            if(checkDecimalBimodal >= 4){
                //cout <<"Prediction:\t" <<"true"<<endl;
            }
            else{
                //cout <<"Prediction:\t" <<"false"<<endl;
            }
            predictOutcome = bimodalPredictionHybrid(bPTIndex, takenOrNot, checkDecimalBimodal);
        }
        
        //increment chooser table
        if(predictOutcome == 0){
            noOfMisPreHybrid++;
        }
        
        //GBHR
        if(takenOrNot == "t"){
            gbhrHybrid.insert(0, "1");
            gbhrHybrid.pop_back();
        }
        //if not taken
        if(takenOrNot == "n"){
            gbhrHybrid.insert(0, "0");
            gbhrHybrid.pop_back();
        }
        //cout << "BHR now set to :\t" << gbhrHybrid<<endl;
        
        //CHOOSER TABLE UPDATE
        if((chooserInputGshare == 1) && (chooserInputBimodal == 0)){
            //increment
            if(checkDecimalHybrid < 3){
                checkDecimalHybrid = checkDecimalHybrid + 1;
            }
        }
        
        if((chooserInputBimodal == 1) && (chooserInputGshare == 0)){
            //decrement
            //noOfMisPreHybrid++;
            if(checkDecimalHybrid > 0){
                checkDecimalHybrid = checkDecimalHybrid - 1;
            }
            
        }
        //cout<< "New CT value:\t" << checkDecimalHybrid<< endl;
        int updateChooserTable = decToBinary(checkDecimalHybrid);
        //cout  << updateChooserTable << endl;
        chooserTableHybrid.at(CTIndex) = updateChooserTable;
        //cout<<"CTIndex,val-"<<CTIndex<<","<<chooserTableHybrid.at(CTIndex) <<endl;
        i++;
        //cout << endl;
        getline(file, line);
        
    }
    file.close();
    
    cout << "OUTPUT" <<endl;
    cout << "Number of predictions:\t" <<i << endl;
    cout << "Number of mispredictions:\t" << noOfMisPreHybrid <<endl;
    double mispredictionsRate = (noOfMisPreHybrid/i)*100;
    cout << "Misprediction Rate:\t" << mispredictionsRate <<"%" <<endl;
    
    cout << "FINAL CHOOSER TABLE CONTENTS" <<endl;
    for(int i = 0; i < noOfEntryhybrid; i++){
        int checkBinary = chooserTableHybrid.at(i);
        int checkDecimal = binaryIntToDecimal(checkBinary);
        cout<< i <<"\t" <<checkDecimal<< endl;
    }
    
    
    cout << "FINAL GSHARE CONTENTS" <<endl;
    for(int i = 0; i < noOfEntryGshare; i++){
        int checkBinary = predictionTableHybridGshare.at(i);
        int checkDecimal = binaryIntToDecimal(checkBinary);
        cout<< i <<"\t" <<checkDecimal<< endl;
    }
    cout << "FINAL BIMODAL CONTENTS" <<endl;
    for(int i = 0; i < noOfEntryBimodal; i++){
        int checkBinary = predictionTableHybridBimodal.at(i);
        int checkDecimal = binaryIntToDecimal(checkBinary);
        cout<< i <<"\t" <<checkDecimal<< endl;
    }
}

void gshareFlow(int m1, int n, string fileName){
    
    int startIndex = 0;
    int endIndex = 0;
    
    ifstream file;
    string line;
    /*
     int m1 = atoi(argv[2]);
     int n = atoi(argv[3]);
     string fileName = argv[4];
     */
    
    for(int i=0 ; i<n ; i++){
        gbhr.append("0");
    }
    //get 2^m
    int base = 2,exponent = m1,s,noOfEntry=1;
    for( s=exponent ; s>0 ; s--)
    {
        noOfEntry = noOfEntry * base;
    }
    
    //create prediction table
    int j=0;
    while(j < noOfEntry) {
        predictionTableGshare.push_back(100);
        j++;
    }
    
    file.open(fileName);
    int i = 0;
    getline(file, line);
    while(!file.eof()){
        //cout << "<line "  << " #" << i << ">\t" << line <<endl;
        istringstream ss(line);
        
        string binaryString = "";
        int decimalNumber = 0;
        int binaryNumber = 0;
        string word;
        ss >> word;
        
        //get hexadecimal and taken/nottaken value
        vector <string> tokens;
        stringstream check1(line);
        string intermediate;
        while(getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }
        string takenOrNot = tokens[1];
        
        binaryString = HexToBin(word);
        //discard last bits
        
        startIndex = binaryString.length() - (n+2);
        endIndex = n;
        string xorPCBits = binaryString.substr(startIndex,endIndex);
        string xorResult = myXOR(xorPCBits, gbhr,n);
        
        startIndex = binaryString.length() - (m1+2);
        endIndex = m1 - n;
        //cout << "start - "<<startIndex<<" end-"<<endIndex<<endl;
        //cout << "Binary: "<< binaryString <<endl;
        string newBinaryString = binaryString.substr(startIndex, endIndex);
        newBinaryString.append(xorResult);
        
        //cout << "Decimal:" << newBinaryString <<endl;
        decimalNumber = binaryStringToDecimal(newBinaryString);
        //cout << "PT index:\t" << decimalNumber << endl;
        gsharePrediction(decimalNumber, takenOrNot);
        if(takenOrNot == "t"){
            gbhr.insert(0, "1");
            gbhr.pop_back();
        }
        else{
            gbhr.insert(0, "0");
            gbhr.pop_back();
        }
        //cout << "BHR now set to :\t" << gbhr<<endl;
        i++;
        //cout << endl;
        getline(file, line);
        
    }
    file.close();
    
    cout << "OUTPUT" <<endl;
    cout << "Number of predictions:\t" <<i << endl;
    cout << "Number of mispredictions:\t" << noOfMisPreGshare <<endl;
    double mispredictionsRate = (noOfMisPreGshare/i)*100;
    cout << "Misprediction Rate:\t" << mispredictionsRate <<"%" <<endl;
    /*
     cout << "FINAL GHSARE CONTENTS" <<endl;
     for(int i = 0; i < noOfEntry; i++){
     int checkBinary = predictionTableGshare.at(i);
     int checkDecimal = binaryIntToDecimal(checkBinary);
     cout<< i <<"\t" <<checkDecimal<< endl;
     }*/
}

void bimodalFlow(int m2,string fileName){
    int startIndex = 0;
    int endIndex = 0;
    
    ifstream file;
    string line;
    
    //int m2 = atoi(argv[2]);
    //string fileName = argv[3];
    
    //get 2^m
    int base = 2,exponent = m2,s,noOfEntry=1;
    for( s=exponent ; s>0 ; s--)
    {
        noOfEntry = noOfEntry * base;
    }
    
    //create prediction table
    int j=0;
    while(j < noOfEntry) {
        predictionTableBimodal.push_back(100);
        j++;
    }
    
    file.open(fileName);
    int i = 0;
    getline(file, line);
    while(!file.eof()){
        
        //cout << "<line "  << " #" << i << ">\t" << line <<endl;
        //getline(file, line);
        istringstream ss(line);
        
        string binaryString = "";
        int decimalNumber = 0;
        int binaryNumber = 0;
        string word;
        ss >> word;
        
        //get hexadecimal and taken/nottaken value
        vector <string> tokens;
        stringstream check1(line);
        string intermediate;
        while(getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }
        string takenOrNot = tokens[1];
        
        binaryString = HexToBin(word);
        //discard last bits
        startIndex = binaryString.length() - (m2+2);
        endIndex = m2;
        //cout << "start - "<<startIndex<<" end-"<<endIndex<<endl;
        //cout << "Binary: "<< binaryString <<endl;
        string newBinaryString = binaryString.substr(startIndex, endIndex);
        //cout << "Decimal:" << newBinaryString <<endl;
        decimalNumber = binaryStringToDecimal(newBinaryString);
        //cout << "PT index:\t" << decimalNumber << endl;
        bimodalPrediction(decimalNumber, takenOrNot);
        i++;
        //cout << endl;
        getline(file, line);
    }
    file.close();
    
    cout << "OUTPUT" <<endl;
    cout << "Number of predictions:\t" <<i << endl;
    cout << "Number of mispredictions:\t" << noOfMisPreBimodal <<endl;
    double mispredictionsRate = (noOfMisPreBimodal/i)*100;
    cout << "Misprediction Rate:\t" << mispredictionsRate <<"%" <<endl;
    
    cout << "FINAL BIMODAL CONTENTS" <<endl;
    for(int i = 0; i < noOfEntry; i++){
        int checkBinary = predictionTableBimodal.at(i);
        int checkDecimal = binaryIntToDecimal(checkBinary);
        cout<< i <<"\t" <<checkDecimal<< endl;
    }
}

int main(int argc, char *argv[])
{
    
    if(!strcmp(argv[1], "hybrid")){
        int k = atoi(argv[2]);
        int m1 = atoi(argv[3]);
        int n = atoi(argv[4]);
        int m2 = atoi(argv[5]);
        string fileName = argv[6];
        hybridFlow(k,m1,n,m2,fileName);
    }
    else if(!strcmp(argv[1], "gshare")){
        int m1 = atoi(argv[2]);
        int n = atoi(argv[3]);
        string fileName = argv[4];
        gshareFlow(m1, n, fileName);
    }
    
    else if(!strcmp(argv[1], "bimodal")){
        int m2 = atoi(argv[2]);
        string fileName = argv[3];
        bimodalFlow(m2, fileName);
    }
    return 0;
}

