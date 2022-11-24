#include "dpr.hpp"

vector<Circonscription> brute(vector<Municipalite> &municipalities, int &nb_circ)
{
    vector<Circonscription> loosing;
    vector<Circonscription> winning;
    vector<Circonscription> complete;
    int maxSize = ceil((float)municipalities.size() / nb_circ);
    int minSize = floor((float)municipalities.size() / nb_circ);
    cout<<"Min size : "<<minSize<<" Max: "<<maxSize<<endl;
    // segregate loosing municipalities from winning ones
    for (auto &mun : municipalities)
    {
        Circonscription circ;
        circ.addMunicipalite(mun, maxSize);
        if (circ.isWinning())
        {
            winning.push_back(circ);
        }
        else
        {
            loosing.push_back(circ);
        }
    }

    // merge if it makes us win
    auto winCirc = winning.begin();
    while (winCirc != winning.end())
    {
        auto lostCirc = loosing.begin();
        while (lostCirc != loosing.end())
        {

            int totalSize = lostCirc->getCount() + winCirc->getCount();
            int totalVotes = lostCirc->getVotes() + winCirc->getVotes();
            // cout << "total size: " << totalSize << endl;
            if (totalSize < maxSize && (float)totalVotes / totalSize > 50)
            {
                winCirc->addCirconscription(*lostCirc, maxSize);
                loosing.erase(lostCirc);
            }
            else
                ++lostCirc;
        }
            if (winCirc->getCount() >= minSize)
            {
                complete.push_back(*winCirc);
                winning.erase(winCirc);
                break;
            }
            else
                ++winCirc;
    }
    cout << "Completed :" << endl;
    for (auto &circ : complete)
    {
        circ.print();
        cout << endl;
    }
    cout << endl
         << "Winning" << endl;
    for (auto &circ : winning)
    {
        circ.print();
        cout << endl;
    }
    cout << endl
         << "loosing " << endl;
    for (auto &circ : loosing)
    {
        circ.print();
        cout << endl;
    }

    return complete;
}
