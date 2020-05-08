//
// Created by convez on 05/05/2020.
//

#ifndef SIMPLESNAKE_SNAKESECTIONSTATUSFIELD_H
#define SIMPLESNAKE_SNAKESECTIONSTATUSFIELD_H

#include "base/BaseEnumField.h"

namespace convez::games::fields {

class SnakeSectionStatusField: public lib::fields::base::BaseEnumField<SnakeSectionStatusField> {
public:
    typedef enum{
        k_Unknown,
        k_HeadPieceUp,
        k_HeadPieceDown,
        k_HeadPieceLeft,
        k_HeadPieceRight,
        k_TailPieceUp,
        k_TailPieceDown,
        k_TailPieceLeft,
        k_TailPieceRight,
        k_LinePieceHoriz,
        k_LinePieceVert,
        k_CornerUpLeft,
        k_CornerUpRight,
        k_CornerDownLeft,
        k_CornerDownRight,
        k_LastValue
    }Labels;

    SnakeSectionStatusField():lib::fields::base::BaseEnumField<SnakeSectionStatusField>(){}
    explicit SnakeSectionStatusField(const Labels& iValue): lib::fields::base::BaseEnumField<SnakeSectionStatusField>(iValue){}
    SnakeSectionStatusField(const SnakeSectionStatusField& iOther): lib::fields::base::BaseEnumField<SnakeSectionStatusField>(iOther){}

    static lib::fields::base::BaseEnumField<SnakeSectionStatusField>::LabelToStringMap_t _LabelToStringMap;
};

}
#endif //SIMPLESNAKE_SNAKESECTIONSTATUSFIELD_H
