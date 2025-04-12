#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    std::ifstream infile("data.txt");
    if(!infile) {
        std::cerr << "Errore nell'apertura del file data.txt" << std::endl;
        return 1;
    }
    string line;
    double S = 0.0;
    int n = 0;

    if (getline(infile,line)) {
        string token;
        stringstream ss(line);
        getline(ss,token,';');
        getline(ss,token);
        S = stod(token);
    }

    if (getline(infile,line)) {
        string token;
        stringstream ss(line);
        getline(ss,token,';');
        getline(ss,token);
        n=stoi(token);
    }
    // Salto la riga w;r 
    getline(infile,line);

    //Creo degli array con una grandezza abbastanza grande da poter contenere i vari w e r
    const int maxAssets = 100;
    double w[maxAssets] = {0.0};
    double r[maxAssets] = {0.0};

    for (int i = 0 ; i < n ; i++) {
        if (getline(infile,line)) {
            string token;
            stringstream ss(line);
            getline(ss,token,';');
            w[i] = stod(token);
            getline(ss,token);
            r[i]= stod(token);
        }
    }
    infile.close();

    double returnRate = 0;
    for (int i = 0 ; i < n ; i++) {
        returnRate += w[i]*r[i];
    }

    double V = (1 + returnRate) * S;

    //Imposto la notazione scientifica
    cout << fixed << setprecision(2);
    cout << "S = " << S << ", n = " << n << "\n";
    cout << "w = [ ";
    for (int i = 0 ; i < n ; i++) {
        cout << w[i] << " ";
    }
    cout << "]" << "\n";
    
    cout << "r = [ ";
    for (int i = 0 ; i < n ; i++) {
        cout << r[i] << " ";
    }
    cout << "]" << "\n";
    // Per il rate del portfolio riporto la precisione a 4 cifre decimali
    cout << "Rate of return of the portfolio: " << fixed << setprecision(4) << returnRate << "\n";
    cout << "V: " << fixed << setprecision(2) << V << "\n";

    std::ofstream outfile("results.txt");
    if (!outfile) {
        std::cerr << "Errore nell'apertura del file result.txt" << std::endl;
        return 1;
    }
    
    outfile << fixed << setprecision(2);
    outfile << "S = " << S << ", n = " << n << "\n";
    outfile << "w = [ ";
    for (int i = 0 ; i < n ; i++) {
        outfile << w[i] << " ";
    }
    outfile << "]" << "\n";
    
    outfile << "r = [ ";
    for (int i = 0 ; i < n ; i++) {
        outfile << r[i] << " ";
    }
    outfile << "]" << "\n";
    outfile << "Rate of return of the portfolio: " << fixed << setprecision(4) << returnRate << "\n";
    outfile << "V: " << fixed << setprecision(2) << V << "\n";
    
    outfile.close();
    return 0;
}
