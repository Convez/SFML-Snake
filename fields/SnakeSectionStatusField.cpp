//
// Created by convez on 05/05/2020.
//

#include "SnakeSectionStatusField.h"

namespace convez::games::fields{
lib::fields::base::BaseEnumField<SnakeSectionStatusField>::LabelToStringMap_t SnakeSectionStatusField::_LabelToStringMap =
{
    {k_Unknown,         "UNKNOWN"},
    {k_HeadPieceUp,       "HeadUp"},
    {k_HeadPieceDown,       "HeadDown"},
    {k_HeadPieceLeft,       "HeadLeft"},
    {k_HeadPieceRight,       "HeadRight"},
    {k_TailPieceUp,       "TailUp"},
    {k_TailPieceDown,       "TailDown"},
    {k_TailPieceLeft,       "TailLeft"},
    {k_TailPieceRight,       "TailRight"},
    {k_LinePieceHoriz,  "Line Horizontal"},
    {k_LinePieceVert,  "Line Vertical"},
    {k_CornerUpLeft,    "CornerUpLeft"},
    {k_CornerUpRight,   "CornerUpRight"},
    {k_CornerDownLeft,  "CornerDownLeft"},
    {k_CornerDownRight, "CornerDownRight"},
    {k_LastValue,       "LAST_VALUE"}
};

}
