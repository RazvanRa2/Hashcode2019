#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct photo{
    set<string> tags;
    char orientation; // V = true, H = false
    int index;
};

struct slide{
    set<string> tags;
    vector<int> photos;
};

int minimum(int x1, int x2, int x3) {
    int mini = x1;

    if (x2 < mini && x2 < x3) {
        return x2;
    }
    if (x3 < mini && x3 < x2) {
        return x3;
    }
    return mini;
}

int interestFactor(slide s1, slide s2) {
    set<string> intersection;
    set<string> diff1;
    set<string> diff2;


    set_intersection(s1.tags.begin(), s1.tags.end(), s2.tags.begin(), s2.tags.end(),
                     inserter(intersection, intersection.begin()));

    set_difference(s1.tags.begin(), s1.tags.end(), s2.tags.begin(), s2.tags.end(),
                   inserter(diff1, diff1.begin()));

    set_difference(s2.tags.begin(), s2.tags.end(), s1.tags.begin(), s1.tags.end(),
                   inserter(diff2, diff2.begin()));

    return minimum((int)intersection.size(), (int)diff1.size(), (int)diff2.size());

}




int main() {

    int nr_slides = 0;
    int nr_vert = 0;
    int nr_photos;

    cin >> nr_photos;

    vector<photo> photos;
    vector<slide> slides;


    for (int i = 0; i < nr_photos; i++){
        photo p;
        char c;
        int nr_tags;
        cin >> c >> nr_tags;

        p.orientation = c;
        p.index = i;

        for(int j = 0; j < nr_tags; j++) {
            string tag;
            cin >> tag;
            p.tags.insert(tag);
        }
        if (p.orientation == 'V') {
            photos.push_back(p);
        } else {
            slide s;
            s.tags = p.tags;
            s.photos.push_back(p.index);
            slides.push_back(s);
        }
    }

    //sort verticals
    int i = 0;
    while (photos.size() > 2){

        int most_different = i + 1;
        int tags_different = 0;
        for (int j = i + 1; j < photos.size(); j++) {
            set<string> reuniune;
            set_union(photos[i].tags.begin(), photos[i].tags.end(), photos[j].tags.begin(), photos[j].tags.end(),
                      inserter(reuniune, reuniune.begin()));

            if (reuniune.size() > tags_different) {
                tags_different = (int)reuniune.size();
                most_different = j;
            }
        }

        slide s;
        s.photos.push_back(photos[i].index);
        s.photos.push_back(photos[most_different].index);

        set_union(photos[i].tags.begin(), photos[i].tags.end(), photos[most_different].tags.begin(),
                  photos[most_different].tags.end(),
                  inserter(s.tags, s.tags.begin()));

        slides.push_back(s);
        
        photos.erase(photos.begin() + most_different);
        photos.erase(photos.begin() + i);
    }

    if (photos.size() == 2) {
        slide s;
        s.photos.push_back(photos[0].index);
        s.photos.push_back(photos[1].index);
        set_union(photos[0].tags.begin(), photos[0].tags.end(), photos[1].tags.begin(),
                  photos[1].tags.end(),
                  inserter(s.tags, s.tags.begin()));
        
        slides.push_back(s);
    }


    // nr_slides += nr_vert % 2 ? nr_vert/2  + 1: nr_vert/2;

    //cout << interestFactor(slides[0], slides[2]) << "\n";
    //cout << slides.size() << endl;
    
    vector<slide> orderedslides;
    orderedslides.push_back(slides[0]);
    vector<bool> used(slides.size(), false);
    used[0] = true;
    for (int  i = 1; i < slides.size(); i++){
        slide selectedSlide;
        int maxScore = -1;
        int indx = -1;

        for (int j = 0; j < slides.size(); j++) {
            if (!used[j]) {

                int currScore = interestFactor(orderedslides[i - 1], slides[j]);

                if (currScore > maxScore) {
                    maxScore = currScore;
                    selectedSlide = slides[j];
                    indx = j;
                }
            }
        }
        //cout << indx << endl;
        used[indx] = true;
        orderedslides.push_back(selectedSlide);
    }
    
    cout << orderedslides.size() << "\n";
    for (int i = 0; i < orderedslides.size(); i++) {
        for (int j = 0; j < orderedslides[i].photos.size();j++) {
            cout << orderedslides[i].photos[j] << " ";
        }
        cout << "\n";
    }
    
    /*
    cout << slides.size() << "\n";
    for (int i = 0; i < slides.size(); i++) {
        for (int j = 0; j < slides[i].photos.size();j++) {
            cout << slides[i].photos[j] << " ";
        }
    */
    

    return 0;
}