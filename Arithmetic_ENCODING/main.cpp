#include <bits/stdc++.h>

using namespace std;

const int maxN = 10000;
int source_length, k;
string source, seq, output="";
float prob[maxN], cdf[maxN], L=0, U=1, L1=0, U1=1, smallestInterval = 1;

unordered_map<char, int> x;

int main()
{
    freopen("input.txt", "rt", stdin);

    cin >> source;
    source_length = source.size();

     //get source set and probabilities
    for(int i=0; i<source_length; i++){
        cin>>prob[i];
        cdf[i] = prob[i];
        for (int j=0; j<i; j++) {
            cdf[i] += prob[j];
        }

        if(i != 0){
            if(cdf[i] - cdf[i - 1] < smallestInterval)
                smallestInterval = cdf[i] - cdf[i - 1] ;
        }
    }
    //cout<< "Please enter sequence"<<endl;

    cin>> seq;

    k = ceil(log2(1/smallestInterval));
    cout << "k = " << k << endl;


    for(int i = 0; i < source_length; i++){
        x[source[i]] = i + 1;
    }

    cout << source << endl;
    cout << seq << endl;




    for (int i=0; i<seq.length(); i++) {

        cout << "X = " << x[seq[i]] << endl;

        // calculate L, U
        if (x[seq[i]] != 1){
            L = ( L1 + ( (U1-L1) * cdf[x[seq[i]] - 2]));
        }else{
            L = L1;
        }

        U = ( L1 + ( (U1-L1)* cdf[x[seq[i]] - 1] ) );

        L1 = L;
        U1 = U;
        cout << "L = " << L << "   U = " << U << endl;
        while ( (L1 < .5 && U1 < .5 ) || ( L1 > .5 && U1 > .5 ) ) {
            cout << "rescale" << endl;
            if ( L1 < .5 && U1 < .5 ) {
                L1 = 2 * L1;
                U1 = 2 * U1;
                output += '0';
            } else {
                L1 = 2*(L1 - .5);
                U1 = 2*(U1 - .5);
                output += '1';
            }
            cout << "to" << endl;
            cout << "L = " << L << "   U = " << U << endl;
        }
        cout << "\n\n\n";
    }

    //add .5
    for(int i = 0; i < k; i++){
        output += (i == 0)? '1' : '0';
    }
    cout<< output<<endl;

    return 0;
}
