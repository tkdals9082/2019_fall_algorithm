#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;


const int DEFAULT_NUM = 10;

int swap(int &a, int &b);
int shuffle(int* a, int length);
void init_1d_array(int*& arr, int length, int initial_val=0);
void init_2d_array(int**& mat, int row, int col, int initial_val=0);
void print_1d_array(int* arr, int length);
void print_2d_array(int** mat, int row, int col);


class GS_STRUCT{
private:
    int man_num;
    int woman_num;
    int** man_pref;
    int** woman_pref;
    int** inverted_pref;
    int* wife;
    int* husband;
    int* count;
    queue<int> poor_man;
public:
    GS_STRUCT();
    GS_STRUCT(int m, int w);
    ~GS_STRUCT();
    void set_man_num(int m){man_num = m;};
    void set_woman_num(int w){woman_num = w;};
    int get_man_num(){return man_num;};
    int get_woman_num(){return woman_num;};
    
    void set_pref();
    int** get_man_pref(){return man_pref;};
    int* get_man_pref(int i){return man_pref[i];};
    int get_man_pref(int i, int j){return man_pref[i][j];};
    int** get_woman_pref(){return woman_pref;};
    int* get_woman_pref(int i){return woman_pref[i];};
    int get_woman_pref(int i, int j){return woman_pref[i][j];};

    void set_inverted_pref();
    int** get_inverted_pref(){return inverted_pref;};
    int* get_inverted_pref(int i){return inverted_pref[i];};
    int get_inverted_pref(int i, int j){return inverted_pref[i][j];};

    int get_count(int man){return count[man];};
    void increase_count(int man){count[man]++;};

    int* get_wife(){return wife;};
    int get_wife(int man){return wife[man];};

    int* get_husband(){return husband;};
    int get_husband(int woman){return husband[woman];};

    void gs_match();
};

GS_STRUCT::~GS_STRUCT(){
    for(int i=0;i<man_num;i++){
        delete[] man_pref[i];
    }
    delete man_pref;
    for(int i=0;i<woman_num;i++){
        delete[] woman_pref[i];
        delete[] inverted_pref[i];
    }
    delete woman_pref;
    delete inverted_pref;
    delete wife;
    delete husband;
    delete count;
}

GS_STRUCT::GS_STRUCT(){
    man_num = DEFAULT_NUM;
    woman_num = DEFAULT_NUM;
    init_2d_array(man_pref,man_num,woman_num);
    init_2d_array(woman_pref,woman_num,man_num);
    init_2d_array(inverted_pref,woman_num,man_num);
    init_1d_array(wife,man_num, -1);
    init_1d_array(husband,woman_num, -1);
    init_1d_array(count,man_num);
    
    set_pref();
    set_inverted_pref();
}

GS_STRUCT::GS_STRUCT(int m, int w){
    man_num = m;
    woman_num = w;
    init_2d_array(man_pref,man_num,woman_num);
    init_2d_array(woman_pref,woman_num,man_num);
    init_2d_array(inverted_pref,woman_num,man_num);
    init_1d_array(wife,man_num, -1);
    init_1d_array(husband,woman_num, -1);
    init_1d_array(count,man_num);
    
    set_pref();
    set_inverted_pref();
}

void GS_STRUCT::set_pref(){
    srand(time(0));
    for(int i=0;i<man_num;i++){
        for(int j=0;j<woman_num;j++){
            man_pref[i][j] = j;
        }
        shuffle(man_pref[i], woman_num);
    }
    for(int i=0;i<woman_num;i++){
        for(int j=0;j<man_num;j++){
            woman_pref[i][j] = j;
        }
        shuffle(woman_pref[i], man_num);
    }
}

void GS_STRUCT::set_inverted_pref(){
    for(int i=0;i<woman_num;i++){
        for(int j=0;j<man_num;j++){
            inverted_pref[i][woman_pref[i][j]] = j;
        }
    }
}

void GS_STRUCT::gs_match(){
    for(int i=0;i<man_num;i++){
        poor_man.push(i);
    }
    while(!poor_man.empty()){
        int man = poor_man.front();
        int best_valid = man_pref[man][count[man]];
        if(husband[best_valid] == -1){
            wife[man] = best_valid;
            husband[best_valid] = man;
            poor_man.pop();
        }
        else if(inverted_pref[best_valid][man] < husband[best_valid]){
                wife[husband[best_valid]] = -1;
                poor_man.push(husband[best_valid]);
                wife[man] = best_valid;
                husband[best_valid] = man;
                poor_man.pop();
        }
        else if(count[man] >= woman_num-1){
            poor_man.pop();
        }
        increase_count(man);
    }
}

int swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
    return 0;
}

int shuffle(int* a, int length){
    for(int i=0; i<length; i++){
        int idx = rand()%length;
        int temp = a[i];
        a[i] = a[idx];
        a[idx] = temp;
    }
    return 0;
}

void init_1d_array(int*& arr, int length, int initial_val){
    arr = new int[length];
    for(int i=0;i<length;i++){
        arr[i] = initial_val;
    }
}

void init_2d_array(int**& mat, int row, int col, int initial_val){
    mat = new int*[row];
    for(int i=0;i<row;i++){
        init_1d_array(mat[i],col,initial_val);
    }
}

void print_1d_array(int* arr, int length){
    cout << "[";
    for(int i=0;i<length;i++){
        cout << " " << arr[i];
    }
    cout << "]" << endl;
}

void print_2d_array(int** mat, int row, int col){
    cout << "[";
    for(int i=0; i<row; i++){
        cout << "[";
        for(int j=0; j<col; j++){
            cout << " " << mat[i][j];
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}


int main(){
    GS_STRUCT gs = GS_STRUCT(100,100);
    gs.gs_match();
    print_2d_array(gs.get_man_pref(), gs.get_man_num(), gs.get_woman_num());
    print_2d_array(gs.get_woman_pref(), gs.get_woman_num(), gs.get_man_num());
    print_2d_array(gs.get_inverted_pref(), gs.get_woman_num(), gs.get_man_num());
    print_1d_array(gs.get_wife(), gs.get_man_num());
}