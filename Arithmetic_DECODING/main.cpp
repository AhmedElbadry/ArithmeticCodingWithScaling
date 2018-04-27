#include <bits/stdc++.h>
#include <bitset>
using namespace std;

const int maxN = 10000;

int source_length, k, n, shift=0;
float min_interval, dTag=0;
string source, t, tag="";
float prob[maxN], cdf[maxN], L=0, U=1, L1=0, U1=1;

int main()
{
    freopen("input.txt", "rt", stdin);


    //cout << "Please enter source set length" << endl;


    cin >> source;
    source_length = source.size();

    for(int i=0; i<source_length; i++){

        //cout<<"Enter entry "<< i+1 <<" probability"<<endl;
        cin>>prob[i];
        cdf[i] = prob[i];
        if(i != 0){
            cdf[i] = cdf[i - 1] + prob[i];
        }

        cout << cdf[i] << " ";

    }

    cout << endl;

    //cout<< "Enter TAG"<<endl;
    cin>>t;


    min_interval = cdf[0];
    for (int i=1; i<source_length;i++) {
        min_interval = min(min_interval, cdf[i]-cdf[i-1]);
    }

    k = ceil( -log2f(min_interval) );
    for (int i=0; i<k;i++){
        tag += t[i];
    }

    cout << "K = " << k << endl;

    int p = 1;
    for(int i=0; i<tag.length() ;i++){
        dTag += ( (tag[i]-'0') * pow(2, -p));
        p++;
    }
    cout << "tag value = " << dTag << endl;

    int symbols[maxN], x;


        cout << "tag.size() - shift " << tag.size() - shift << endl;

        int f = 1;
        for(int i=0; f ;i++) {
        x = 1;

        if(tag.size() - shift <= 0){
            f = 0;
        }

        while(x <= source_length){
            if (x!=1){
                L = ( L1 + ( (U1-L1)*cdf[x-2] ) );
            }
            U = ( L1 + ( (U1-L1)*cdf[x-1] ) );
            cout << " L = " << L << "    U = " << U << endl;
            if (L < dTag && U > dTag){
                cout << "taken   X = " << x << endl;
                cout << " L = " << L << "    U = " << U << endl;
                symbols[i] = x;
                cout<< "tag = " << dTag;
                while ( (L < .5 && U <= .5 ) || ( L >= .5 && U > .5 ) ) {

                    // shift by 1
                    shift++;
                    for (int j = k-1; j>=0 ;j--) {
                        tag[j] = t[j+shift];
                    }

                    p = 1;
                    dTag = 0;
                    for(int z=0; z<tag.length() ;z++){
                        dTag += ( (tag[z]-'0') * pow(2, -p) );
                        p++;
                    }

                    if ( L < .5 && U <= .5 ) {
                        L = 2 * L;
                        U = 2 * U;
                    } else if (( L >= .5 && U > .5 )) {
                        L = 2*(L - .5);
                        U = 2*(U - .5);
                    }
                    cout << "\n to" << endl;
                    cout << " L = " << L << "    U = " << U << endl;

                }

                L1 = L;
                U1 = U;
                break;
            }

            x++;
        }
        n++;

        cout << "\n\n\n";

    }


    for (int i =0; i<n ;i++) {
        cout<< source[symbols[i]-1];
    }

    return 0;
}





