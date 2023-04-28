#include <iostream>
#include <deque>
#include <vector>

int main ()
{
    //assign flag variable
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    //input the numbers for each card
    int number;
    while (std::cin>>number) {
        if(number == 0){
            break;
        }
        else if (number < 0){
            std::cout << "Mana ada kartu minus!\n";
            continue;
        }

//        see documentation: https://cplusplus.com/reference/deque/deque/
//      declare dequeue of discarded cards and remaining cards
        std::deque<int> discarded_cards, remaining_cards(number);

        for(int i = 0; i < number; i++)
        {
            //pushes next number behind first number and so on
            remaining_cards[i] = i+1;
        }

        //flag variable to indicate whether we should discard or move the card
        bool should_discard = true;
        // does the process until the remaining cards is 1 left
        while ((int)remaining_cards.size() > 1){
            if (should_discard ){
                // .front() = fetches the first element in the remaining cards deque
                int first_card = remaining_cards.front();
                //pushes first card into the discarded cards deque
                discarded_cards.push_back(first_card);
                remaining_cards.pop_front();
                should_discard = false;
            }
            if (should_discard == false)
            {
                // the first element is now the remaining card
                int first_card = remaining_cards.front();
                // push the first element back
                remaining_cards.push_back(first_card);
                //delete the first card and we have a new card in the first element
                remaining_cards.pop_front();
                should_discard = true;
            }
        }

        std::cout << "Discarded cards: ";
        for( int i = 0; i < (int)discarded_cards.size(); i++)
        {
            std::cout << discarded_cards[i];
            if (i != (int)discarded_cards.size() - 1) {
                std::cout << ", ";
            }
        }

        std:: cout << "\nRemaining card: "<< remaining_cards.front() << "\n";
    };

    return 0;
}

