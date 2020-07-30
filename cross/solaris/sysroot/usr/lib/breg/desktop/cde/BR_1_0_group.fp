######################################################################
#
#    Common Desktop Environment (CDE)
#
#    Front Panel Definition File
#
######################################################################

CONTROL BR_1_0
{
    TYPE            icon
    CONTAINER_NAME  Top
    CONTAINER_TYPE  BOX
    POSITION_HINTS  first
    ICON            SDtBR
    LABEL           Solaris Registration
    PUSH_ACTION     BR_1_0_action
}

SUBPANEL BR_1_0_panel
{
    CONTAINER_NAME  BR_1_0
    TITLE           Solaris Registration
}
