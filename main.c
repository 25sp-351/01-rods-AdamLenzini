#include <stdio.h>
#include <stdlib.h>

// Cuts that the user inputs as a possiblity for the rod
// length - the length of the cut
// price - how much the cut is valued
struct cut {
    int length;
    int price;
};

// Cuts that are made to the rod
// length - the length of the cut
// count - the number of cuts of that length
struct cut_details {
    int length;
    int count;
};

int rod_cutting(int rod_length, int list_size, /*int *cut_count,*/
                struct cut *possible_cuts/*, struct cut_details *cuts_made*/);

int rod_cutting_recursion(int rod_length, int list_size, int cut_count,
                            struct cut *possible_cuts/*, struct cut_details *cuts_made*/);

int main(int argc, char **argv) {

    int rod_length = 0;

    //int cut_count = 0;

    int list_size = 0;

    struct cut *possible_cuts = (struct cut *)malloc(sizeof(struct cut) * 5);

    //struct cut_details *cuts_made = (struct cut_details *)malloc(sizeof(struct cut_details) * rod_length);

    if (argc != 2) {
        printf("Please pass a rod length through the command line\n");
        return 1;
    }

    sscanf(argv[1], "%d", &rod_length);

    //printf("Rod length is %d\n", rod_length);
    
    while (!feof(stdin)) {
        if(2 != fscanf(stdin, "%d, %d", &possible_cuts[list_size].length,
                        &possible_cuts[list_size].price))
            break; 
        //printf("I got here\n");

        list_size++;
        
        if (list_size % 5 == 0) {
            possible_cuts = (struct cut *)realloc(possible_cuts, sizeof(struct cut) * (list_size + 5));
        }
    }

    //printf("I'm done\n");
    // index = 0;

    int max_price = rod_cutting(rod_length, list_size, /*&cut_count,*/ possible_cuts/*, cuts_made*/);

    printf("Max price: %d\n", max_price);

    // printf("Cuts made:\n");
    // for (int i = 0; i < cut_count; i++) {
    //     printf("%d cuts of length %d\n", cuts_made[i].count, cuts_made[i].length);
    // }

    return 0;
}

// Uses recursion to find the most profitable cuts for the rod
// Inputs: rod_length - the length of the rod
//         list_size - the number of possible cuts
//         cut_count - the number of cuts that are made to the rod
//         possible_cuts - array of structs representing the possible
//                         cuts that can be made to the rod
// Output: the maximum price that can be obtained from cutting the rod

int rod_cutting(int rod_length, int list_size, /*int *cut_count,*/ struct cut *possible_cuts/*, struct cut_details *cuts_made*/) {

    int max_price = 0;
    int cut_count = 0;

    max_price = rod_cutting_recursion(rod_length, list_size, cut_count, possible_cuts/*, cuts_made*/);

    return max_price;
}

// Helper function for rod_cutting
// Inputs: rod_length - the length of the rod
//         list_size - the number of possible cuts
//         cut_count - the number of cuts that are made to the rod
//         possible_cuts - array of structs representing the possible
//                         cuts that can be made to the rod
// Output: the maximum price that can be obtained from cutting the rod

int rod_cutting_recursion(int rod_length, int list_size, int cut_count,
                            struct cut *cuts/*, struct cut_details *cuts_made*/) {

    int max_price = 0;

    int price = 0;

    //int index = 0;

    if (rod_length <= 0) {
        return 0;
    }

    for (int ix = 0; ix < list_size; ix++) {
        if (rod_length >= cuts[ix].length) {
            //struct cut_details *temp_cut_list = (struct cut_details *)malloc(sizeof(struct cut_details) * rod_length);
            //int temp_cut_count = 0;

            price = cuts[ix].price + rod_cutting_recursion(rod_length - cuts[ix].length,
                                                            list_size, cut_count++, cuts/*, temp_cut_list*/);

            if (price > max_price) {
                max_price = price;
                //*cut_count = temp_cut_count + 1;

                printf("%d @ %d = %d\n", cut_count, cuts[ix].length,
                        (cuts[ix].price * cut_count));

                // for (int j = 0; j < cut_count; j++) {
                //     cuts_made[j] = temp_cut_list[j];
                // }

                //cuts_made[ix] = temp_cut_list[ix];
                //cuts_made[temp_cut_count].length = cuts[ix].length;
                //cuts_made[temp_cut_count].count = 1;
            }
        }
    }

    return max_price;
}