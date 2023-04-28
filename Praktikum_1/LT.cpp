#include <iostream>
#include <vector>

    int main()
    {
    int q;

    //input number of test cases
    std::cin >> q;

    for (int i = 0; i <q; ++i) {

        //poin tertinggi
        int highest_points = 0;

        std::string s;
        //input FB
        std::cin>>s;

        // inisialisasi current points to 0, because this is where we start
        // checking until < s.length.
        for (int j = 0; j < s.length(); ++j) {
            int current_position = 0;
            int points = 0;

            //
            for (int k = j; k < s.length(); ++k) {
                char current = s[k];

                if (current == 'B') {
                    current_position--;
                } else if (current == 'F') {
                    current_position++;
                }

                //jika current position adalah minus maka invalid alias break
                if (current_position < 0) {
                    break;
                }

                //jika tidak break, maka langkah adalah valid dan diincrement
                points++;

                // Jika current posisi = 0 dan point sekarang overtake highest point
                // maka point sekarang menjadi highest point.
                if (current_position == 0 && points > highest_points) {
                    highest_points = points;
                }
            }
        }

        std::cout<< highest_points << std::endl;
    }



    return 0;
}