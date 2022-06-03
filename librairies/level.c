#include <stdbool.h>

typedef struct Case
{
    unsigned char bloc; // 0->air 1->wall 2->box 3->body
    bool cible;
} case_t;

// typedef struct Level
// {
//     map Map;
    
// } level_t;

case_t* create_case (int bloc, bool cible){
    case_t* case_=(case_t *) malloc(sizeof(case_t));
    case_->bloc = bloc;
    case_->cible = cible;
    return case_
}
