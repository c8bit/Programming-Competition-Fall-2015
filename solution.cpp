#include <iostream>
#include <vector>

using namespace std;

int findClosestTarget(int lt, int rt, int cur);

int main(void){

    int num_stacks = 0,
        i;
    vector<int>    cur(20,-1);
    vector<int> target(20,-1);

    cin >> num_stacks;                                     //FIRST  input line defines NUMBER OF STACKS
    for( i = 0; i < num_stacks; i++ ){ cin >> cur[i];    } //SECOND input line defines CURRENT STACK MAKEUP
    for( i = 0; i < num_stacks; i++ ){ cin >> target[i]; } //THIRD  input line defines DESIRED STACK MAKEUP

    /*****************************/

    int cur_sum    = 0,
        target_sum = 0,
        difference = 0;

    // Calculate block sums in each vector
    for( i = 0; i < num_stacks; i++ ){
        target_sum += target[i];
           cur_sum += cur[i];
    }
    difference = cur_sum - target_sum;

    //  Adjust target vector based on difference between sums
    if( cur_sum != target_sum ){
        for( i = 0; i < num_stacks; i++ ){
            target[i] += difference / num_stacks;
            if( difference % num_stacks > i ){
                cur_sum > target_sum ? target[i]++ : target[i]--;
            }
        }
    }

    /**************************/

    int curp  = 0,
        carry = 0,
        done  = 0,
        l_target = -1,
        r_target = -1,
        d_target = -1;

    vector<int> sfin( num_stacks , 0 );

//MAIN LOOP
while( !done ){

    //FIND CLOSEST EXCESS AND PICK-------------------------
    if( cur[curp] > target[curp] ){
        //pick up
        cout << "P ";
        carry = 1;
        cur[curp]--;
    }
    else{
        //find L_target
        for( i = curp - 1; i >= 0; i-- ){
            if( cur[i] > target[i] ){
                l_target = i;
                break;
            }
        }

        //find R_target
        for( i = curp + 1; i < num_stacks; i++ ){
            if( cur[i] > target[i] ){
                r_target = i;
                break;
            }
        }

        //find closer of 2 targets
        if( !( l_target == -1 && r_target == -1 ) )
            { d_target = findClosestTarget( l_target, r_target, curp); }
        else
            break;

        //go to there
        while( d_target != curp ){
            if( d_target < curp ){
                //go left
                cout << "L ";
                curp--;
            }
            else{
                //go right
                cout << "R ";
                curp++;
            }
        }

        //pick up
        cout << "P ";
        carry = 1;
        cur[curp]--;
    }
    l_target = -1;
    r_target = -1;
    d_target = -1;


    //FIND CLOSEST NEED AND DROP-------------------------
    //find L_target
    for( i = curp - 1; i >= 0 ; i-- ){
        if( cur[i] < target[i] ){
            l_target = i;
            break;
        }
    }
    //find R_target
    for( i = curp + 1; i < num_stacks; i++ ){
        if( cur[i] < target[i] ){
            r_target = i;
            break;
        }
    }

    if( !( l_target == -1 && r_target == -1 ) )
        { d_target = findClosestTarget( l_target, r_target, curp ); }
    else
        break;

    //go to there
    while( d_target != curp ){
        if( d_target < curp ){
            //go left
            cout << "L ";
            curp--;
        }
        else{
            //go right
            cout << "R ";
            curp++;
        }
    }

    //drop
    cout << "D ";
    carry = 0;
    cur[curp]++;
    l_target = -1;
    r_target = -1;
    d_target = -1;

    //EVALUATE CURRENT----------------------------
    if( cur[curp] == target[curp] ) { sfin[curp] = 1; }

    //EVALUATE ALL------------------------------
    for( i = 0 , done = 1; i < num_stacks; i++ ) { done *= sfin[i]; }
}

    cout << "X ";
    return 0;
}

int findClosestTarget(int lt, int rt, int cur){
    int dt;

    if     (lt == -1) { dt = rt; }
    else if(rt == -1) { dt = lt; }
    else{
        if((cur - lt) <= (rt - cur))
            { dt = lt; }
        else
            { dt = rt; }
        }

    return dt;
}
