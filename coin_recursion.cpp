void use_ways( int amount, int denomination )
{
    int count = 0;
    int temp_denomination = 0;

    // Loop through for the denomination quantity, only if the user entered an amount > 0
    while( denomination > 0 && amount > 0 ) {

        // Case where amount is smaller than any given denomination
        while( ways( amount, denomination ) == 0 )
            denomination--;

        // Variables for holding data
        // NOTE:    In order for the function to work, a stack like structure needed to be implemented.
        //          Unfortunately, you cannot stack arrays. This is because of the nature of the
        //          array data structure. So the only option was to create multiple "copies"
        //          distinct_ways_temp is utilized by nickels
        //          distinct_ways_holder is utilized by dimes, as a holder to decrement through dimes, then nickels
        //          distinct_ways_holder_q serves the same purpose of sans _q, but opertes for quarters
        //          This is because when looping all possiblities, you need to reset to orinal tier than decrememnt
        //          more significant bits, and loop the lower section. Let me demonstrate...
        //          Let's assume there is an array of [0][2][1][1], representing quarters, dimes, nickels, and pennies respecitively
        //          Next:   [0][2][0][6]
        //          Next:   [0][1][3][1] <----  This is where the holder was used, because pennies and nickels need to reset
        //                                      before decrementing dimes. Thus the complexity of this program.
        temp_denomination = denomination;
        int amount_remaining = amount;
        int distinct_ways[5] = { 0 };
        int distinct_ways_temp[5] = { 0 };
        int distinct_ways_holder[5] = { 0 };
        int distinct_ways_holder_q[5] = { 0 };


        // Load array of distinct combinations ///////////////////////////
        while( temp_denomination > 0 ) {
            distinct_ways[temp_denomination] = ways(amount_remaining, temp_denomination);
            amount_remaining -= coins(temp_denomination)*distinct_ways[temp_denomination];
            temp_denomination--;
        }
        //////////////////////////////////////////////////////////////////

        // Input denomination is 1, therefore there is no reductions to occur.
        if( denomination == 1 ) {
            for( int i = denomination; i > 0; i-- ){
                if( distinct_ways[i] > 0 )
                    std::cout << distinct_ways[i] << " " << coin_type(i) << ", ";
            }
            std::cout << "\n";
        }

        // For case of nickel
        if( denomination == 2 ){
            for(int j = 0; j < 5; j++ )
                    distinct_ways_temp[j] = distinct_ways[j];

            for( int j = denomination; j > 0; j-- ){
                if( distinct_ways_temp[j] > 0 )
                std::cout << distinct_ways_temp[j] << " " << coin_type(j) << ", ";
            }
            std::cout << "\n";

            while( distinct_ways_temp[2] > 1 ){

                // decrement nickel value
                distinct_ways_temp[2]--;
                // incease penny value
                distinct_ways_temp[1] += ways( coins(2), 1 );

                // print output of each layer
                for( int j = denomination; j > 0; j-- ){
                    if( distinct_ways_temp[j] > 0 )
                    std::cout << distinct_ways_temp[j] << " " << coin_type(j) << ", ";
                }
                std::cout << "\n";
            }
        }

        // Case for dime
        if( denomination == 3 ) {

            // Set the holder
            for(int j = 0; j < 5; j++ )
                distinct_ways_holder[j] = distinct_ways[j];

                for( int j = denomination; j > 0; j-- ){
                    if( distinct_ways_holder[j] > 0 )
                    std::cout << distinct_ways_holder[j] << " " << coin_type(j) << ", ";
                }
                std::cout << "\n";


            while( distinct_ways_holder[3] > 0 ) {

                // Set the temp for nickel maniuplation
                for(int j = 0; j < 5; j++ )
                    distinct_ways_temp[j] = distinct_ways_holder[j];


                    while( distinct_ways_temp[2] > 0){

                        // decrement nickel value
                        distinct_ways_temp[2]--;
                        // incease penny value
                        distinct_ways_temp[1] += ways( coins(2), 1 );

                        // print output of each layer
                        for( int j = denomination; j > 0; j-- ){
                            if( distinct_ways_temp[j] > 0 )
                            std::cout << distinct_ways_temp[j] << " " << coin_type(j) << ", ";
                        }
                        std::cout << "\n";
                    }

                // Update hoolder value
                distinct_ways_holder[3]--;
                distinct_ways_holder[2] += ways( coins(3), 2);

                // Print new set after holder is decremented
                if( distinct_ways_holder[3] > 0 ) {
                    for( int j = denomination; j > 0; j-- ){
                        if( distinct_ways_holder[j] > 0 )
                        std::cout << distinct_ways_holder[j] << " " << coin_type(j) << ", ";
                    }
                    std::cout << "\n";
                }
            }
        }

        if( denomination == 4 ) {

            // Create holder for quarters
            for( int j = 0; j < 5; j++ )
                distinct_ways_holder_q[j] = distinct_ways[j];

            for( int j = denomination; j > 0; j-- ){
                if( distinct_ways_holder_q[j] > 0 )
                    std::cout << distinct_ways_holder_q[j] << " " << coin_type(j) << ", ";
            }
            std::cout << "\n";


            while( distinct_ways_holder_q[4] > 0) {
                // Create holder for dimes, from quarter holder
                for(int j = 0; j < 5; j++ )
                    distinct_ways_holder[j] = distinct_ways_holder_q[j];

                // Same as dime
                if( distinct_ways_holder[3] > 0 ) {
                    while( distinct_ways_holder[3] > 0 ) {

                        for(int j = 0; j < 5; j++ )
                            distinct_ways_temp[j] = distinct_ways_holder[j];


                            while( distinct_ways_temp[2] > 0){

                                // decrement nickel value
                                distinct_ways_temp[2]--;
                                // incease penny value
                                distinct_ways_temp[1] += ways( coins(2), 1 );

                                // print output of each layer
                                for( int j = denomination; j > 0; j-- ){
                                    if( distinct_ways_temp[j] > 0 )
                                    std::cout << distinct_ways_temp[j] << " " << coin_type(j) << ", ";
                                }
                                std::cout << "\n";
                            }


                        distinct_ways_holder[3]--;
                        distinct_ways_holder[2] += ways( coins(3), 2);

                        for( int j = denomination; j > 0; j-- ){
                            if( distinct_ways_holder[j] > 0 )
                            std::cout << distinct_ways_holder[j] << " " << coin_type(j) << ", ";
                        }
                        std::cout << "\n";
                    }
                }
                // If dimes are depleted, but nickels remain, print their possible combinations
                if( distinct_ways_holder[2] > 0 ) {
                    while( distinct_ways_holder[2] > 0){

                        // decrement nickel value
                        distinct_ways_holder[2]--;
                        // incease penny value
                        distinct_ways_holder[1] += ways( coins(2), 1 );

                        // print output of each layer
                        for( int j = denomination; j > 0; j-- ){
                            if( distinct_ways_holder[j] > 0 )
                            std::cout << distinct_ways_holder[j] << " " << coin_type(j) << ", ";
                        }
                        std::cout << "\n";
                    }
                }

                // Update holder
                distinct_ways_holder_q[4]--;
                distinct_ways_holder_q[3] += ways( coins(4), 3 );
                distinct_ways_holder_q[2] += ways( 5, 2 );

                if(distinct_ways_holder_q[4] > 0) {
                    for( int j = denomination; j > 0; j-- ){
                        if( distinct_ways_holder_q[j] > 0 )
                            std::cout << distinct_ways_holder_q[j] << " " << coin_type(j) << ", ";
                    }
                    std::cout << "\n";
                }
            }
        }

    denomination--;
    } // end loop for denomination caps 4,3,2,1
}
