#include "heuristique.hpp"
std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size)
{
    // variable for debugging
    bool verbose = false;

    // variables for code
    std::vector<Circonscription> solution;
    std::vector<Municipalite> muniStart;
    int total = 0;

    for (int i = 0; i < static_cast<int>(munis.size()); i++)
    {
        total += munis[i].votes;
    }

    float freq = munis.size() / float(n_circ);
    int max_size = ceil(freq);
    int min_size = floor(freq);

    if (verbose)
    {
        std::cout << "total amount of votes: " << total << endl;
        std::cout << "min_size: " << min_size << " max_size: " << max_size << endl;
    }

    // create starting points for all the circ
    int idx = 0;

    // rectangular tessellation TODO
    float x = sqrt(x_size / float(y_size) * float(n_circ));
    float y = floor(n_circ / x);
    x = floor(x);
    float aspectRatio = y_size / float(x_size);

    while (x * y < n_circ)
    { // find rough rectangle able to fit all circs, in a similar shape of the map
        adjustAspectRatio(x, y, n_circ, aspectRatio);
    }
    
    if (x * y > n_circ)
    { // if rectangle is too big, try to reduce it to fit better
        adjustAspectRatio(x, y, n_circ, aspectRatio);
    }

    float x_jump;
    float y_jump;
    
    if (x == 1)
    {
        x_jump = 0;
    }
    else
    {
        x_jump = (x_size - 1) / (x - 1);
    }
    
    if (y == 1)
    {
        y_jump = 0;
    }
    else
    {
        y_jump = (y_size - 1) / (y - 1);
    }
    
    if (verbose)
    {
        std::cout << "tesselation in a " << x << " x " << y << " rectangle" << endl;
        std::cout << "x jump: " << x_jump << " y_jump: " << y_jump << endl;
    }
    int m = 0;
    
    while (m < n_circ)
    {
        // initialize backwards so that the filling routine starts with the farthest munis
        for (int i = y - 1; i >= 0; i--)
        {
            for (int j = x - 1; j >= 0; j--)
            {
                if (m < n_circ)
                {
                    idx = round(x_jump * j) + round(y_jump * i) * x_size;
                    Circonscription circ(m);
                    circ.addMunicipalite(munis[idx], dist_max, max_size);
                    muniStart.push_back(munis[idx]);
                    solution.push_back(circ);
                    m++;
                }
            }
        }
    }

    std::vector<Municipalite> muniOrphelines;
    // now that we have starting points fill the space by assigning munis to closest circ, one circ at a time
    bool full_circs = false;
    
    for (auto &municipalite : munis)
    {
        if (municipalite.i_circ == -1)
        { // make sure muni is un-assigned
            int dist_min = dist_max + 1;
            std::vector<int> closest_circs;
            int closest_circ = 0;
            // first fill circ to minimal size, then add remaining munis up to max size
            if (!full_circs)
            {
                full_circs = true;
    
                for (int i = 0; i < n_circ; i++)
                {
                    if (static_cast<int>(solution[i].getCount()) < min_size)
                    {
                        full_circs = false;
                        int dist = solution[i].distance(municipalite, muniStart[i]);
                        if (dist < dist_min)
                        { // found a closer circ
                            dist_min = dist;
                            closest_circ = i;
                            closest_circs.push_back(i);
                        }
                        else if (dist == dist_min)
                        { // same distance, prioritize smaller circs
                            if (solution[i].getCount() < solution[closest_circ].getCount())
                            {
                                dist_min = dist;
                                closest_circ = i;
                                closest_circs.push_back(i);
                            }
                        }
                    }
                }
            }
            else
            { // didn't find a circ with less than min_size munis now add to max size
                for (int i = 0; i < n_circ; i++)
                {
                    if (static_cast<int>(solution[i].getCount()) < max_size)
                    {
                        int dist = solution[i].distance(municipalite, muniStart[i]);
    
                        if (dist < dist_min)
                        {
                            dist_min = dist;
                            closest_circ = i;
                            closest_circs.push_back(i);
                        }
                    }
                }
            }

            if (dist_min <= dist_max)
            {
                bool success = false;
    
                for (int i = closest_circs.size() - 1; i >= 0; i--)
                { // try to add to closest, if not to 2nd closest etc.
                    int i_circ = closest_circs[i];
                    success = solution[i_circ].addMunicipalite(municipalite, dist_max, max_size);
                    if (success)
                    {
                        break;
                    }
                }
                if (!success)
                {
                    muniOrphelines.push_back(municipalite);
                }
            }
            else
            {
                muniOrphelines.push_back(municipalite);
            }
        }
    }

    if (verbose)
    {
        std::cout << "number of orphan munis: " << muniOrphelines.size() << endl;
    }

    // visualize(munis,  x_size, y_size);
    //  monte carlo pour assigner les munis orphelines aux circonscriptions non-complètes
    if (verbose)
    {
        std::cout << "Starting monte carlo to fill solution" << endl;
    }
    
    while (muniOrphelines.size() > 0)
    {
        int smallest_idx;
        int smallest_size = max_size;
    
        // find smallest circ to add a muni to it
        for (int i = 0; i < n_circ; i++)
        {
            int size = solution[i].getCount();
            if (size < smallest_size)
            {
                smallest_size = size;
                smallest_idx = i;
            }
        }

        // first check if we can add one of the remaining munis
        bool success = false;
    
        for (int i = 0; i < static_cast<int>(muniOrphelines.size()); i++)
        {
            // we need to assign from the real set, so find whichs muni this correpsonds to in munis
            int x = muniOrphelines[i].x;
            int y = muniOrphelines[i].y;
            success = solution[smallest_idx].addMunicipalite(munis[x_size * y + x], dist_max, max_size);
            if (success)
            {
                muniOrphelines[i] = muniOrphelines.back();
                muniOrphelines.pop_back();
                break; // we found an orphan, restart the process with updated values
            }
        }
    
        // if not, then steal a random muni from the neighbors
        if (!success)
        {
            // solution[smallest_idx].print();
            Municipalite stolen = solution[smallest_idx].stealNeighbor(solution, munis, x_size, y_size, dist_max, max_size);
            if (stolen.i_circ == -1)
            {
                std::cout << "test" << endl;
        
                for (int i = 0; i < static_cast<int>(muniOrphelines.size()); i++)
                {
                    if (stolen == muniOrphelines[i])
                    {
                        muniOrphelines[i] = muniOrphelines.back();
                        muniOrphelines.pop_back();
                    }
                }
            }
        }
    }

    return solution;
}

bool heuristique(std::vector<Municipalite> &munis, std::vector<Circonscription> &circs, int n_circ, int dist_max, bool p_flag, int x_size, int y_size, float &temperature)
{

    // std::vector<Municipalite> dummy_munis = munis;
    // std::vector<Circonscription> dummy_circs = circs;
    float freq = munis.size() / float(n_circ);
    int max_size = ceil(freq);

    // randomly choose a muni
    int i_muni = std::rand() % munis.size();
    int i_circ = munis[i_muni].i_circ;

    // randomly choose one of her neighbours
    int delta_x = (std::rand() % 3) - 1;
    int delta_y = (std::rand() % 3) - 1;
    int newX = munis[i_muni].x + delta_x;
    int newY = munis[i_muni].y + delta_y;

    // if you can and it improves, swap them
    if (newX >= 0 && newX < x_size && newY >= 0 && newY < y_size)
    {
        int new_circ = munis[x_size * newY + newX].i_circ;
        if (new_circ != i_circ)
        {
            Circonscription dummy_icirc = circs[i_circ];
            Circonscription dummy_newcirc = circs[new_circ];
            Municipalite dummy_imuni = munis[i_muni];
            Municipalite dummy_newmuni = munis[x_size * newY + newX];

            int before = dummy_icirc.isWinning() + dummy_newcirc.isWinning();
            dummy_icirc.removeMunicipalite(dummy_imuni);
            dummy_newcirc.removeMunicipalite(dummy_newmuni);
            bool success1 = dummy_icirc.addMunicipalite(dummy_newmuni, dist_max, max_size);
            bool success2 = dummy_newcirc.addMunicipalite(dummy_imuni, dist_max, max_size);
            int after = dummy_icirc.isWinning() + dummy_newcirc.isWinning();

            if (success1 && success2)
            {
                if (after >= before)
                {
                    circs[i_circ].removeMunicipalite(munis[i_muni]);
                    circs[new_circ].removeMunicipalite(munis[x_size * newY + newX]);
                    circs[i_circ].addMunicipalite(munis[x_size * newY + newX], dist_max, max_size);
                    circs[new_circ].addMunicipalite(munis[i_muni], dist_max, max_size);
                    // std::cout << "improved!" << endl;
                    if (after > before)
                    {
                        if (p_flag)
                        {
                            // print the solution in the good format
                            cout << endl;
                            for (size_t i = 0; i < circs.size(); i++)
                            {
                                circs[i].print();
                            }
                        }
                        else
                        {
                            int count = 0;
                            for (size_t i = 0; i < circs.size(); i++)
                            {
                                // cout << solution[i].getVotes();
                                // cout << endl;
                                count += circs[i].isWinning();
                            }
                            cout << count << endl;
                        }
                    }
                    temperature *= 0.999;
                    return true;
                }
                else
                { // use the temperature to determine if we switch
                    float random = (std::rand() % 100000000) / 1000000.0f;
                    if (after == before - 1)
                    {
                        if (random < temperature / 2.0f)
                        {
                            // std::cout<< "used temp for -1! " << temperature << endl;
                            circs[i_circ].removeMunicipalite(munis[i_muni]);
                            circs[new_circ].removeMunicipalite(munis[x_size * newY + newX]);
                            circs[i_circ].addMunicipalite(munis[x_size * newY + newX], dist_max, max_size);
                            circs[new_circ].addMunicipalite(munis[i_muni], dist_max, max_size);
                        }
                    }
                    else if (after == before - 2)
                    {
                        if (random < temperature / 16.0f)
                        {
                            // std::cout<< "used temp for -2!" << endl;
                            circs[i_circ].removeMunicipalite(munis[i_muni]);
                            circs[new_circ].removeMunicipalite(munis[x_size * newY + newX]);
                            circs[i_circ].addMunicipalite(munis[x_size * newY + newX], dist_max, max_size);
                            circs[new_circ].addMunicipalite(munis[i_muni], dist_max, max_size);
                        }
                    }
                }
            }
        }
    }

    // std::cout << "failed to improve" << endl;
    // temperature *= 1.001;
    return false;
}

void adjustAspectRatio(float &x, float &y, int n_circ, float globalAspectRatio)
{

    // if rectangle is too small, increase it
    if ((x + 1) * y < n_circ)
    { // if adding to x is not enough
        y = y + 1;
        return;
    }
    else if ((y + 1) * x < n_circ)
    { // if adding to y is not enough
        x = x + 1;
        return;
    }

    float aspectRatio_x = y / (x + 1.0f);
    float aspectRatio_y = (y + 1.0f) / x;
    float dx = abs(globalAspectRatio - aspectRatio_x);
    float dy = abs(globalAspectRatio - aspectRatio_y);
    // std::cout << "dx: " << dx << " dy: " << dy << endl;
    if (dx < dy)
    {
        x = x + 1;
    }
    else
    {
        y = y + 1;
    }

    // if to big, reduce it
    if ((x - 1) * y < n_circ)
    { // if reducing x is too much
        while (x * y > n_circ)
        {
            y = y - x;
        }
        y = y + x; // go back to last valid size
    }
    else if ((y - 1 * x) < n_circ)
    {
        while (x * y > n_circ)
        {
            x = x - y;
        }
        x = y + x; // go back to last valid size
    }
}
