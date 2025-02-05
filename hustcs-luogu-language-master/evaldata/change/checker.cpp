#include "testlib.h"

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    while(!ans.eof()){
        double pans = ouf.readDouble();
        double jans = ans.readDouble();
//        ans.readEoln();
//        ouf.readToken(); 

        if (fabs(pans - jans)>0.1)
            quitf(_wa, "The answer is wrong: expected = %f, found = %f", jans, pans);
        pans = ouf.readDouble();
        jans = ans.readDouble();
        if (fabs(pans - jans)>0.1)
            quitf(_wa, "The answer is wrong: expected = %f, found = %f", jans, pans);
        ans.readEoln();
    }
    quitf(_ok, "The answer is correct.");
    return 0;

}
