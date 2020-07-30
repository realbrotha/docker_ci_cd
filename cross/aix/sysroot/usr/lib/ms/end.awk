# @(#)35	1.2 11/21/89 12:34:34
#
# COMPONENT_NAME: (CMDTEXT) Text Formatting Services
#
# FUNCTIONS:
#
# ORIGINS:26
#
#$Header:end.awk 12.0$
#$ACIS:end.awk 12.0$
#$Source: /ibm/acis/usr/src/usr.lib/ms/RCS/end.awk,v $
BEGIN {
	print ".bp"		>  "endnotes"
	print ".nr # 0 1"	>> "endnotes"
	print ".ds # \\\\n+#."	>> "endnotes"
	print ".TL"		>> "endnotes"
	print "ENDNOTES"	>> "endnotes"
	print ".sp"		>> "endnotes"
	}
{
	if ($1 == ".FS") {
		inNote = 1
		print ".IP \\*#" >> "endnotes"
	}
	else if ($1 == ".FE")
		inNote = 0;

	else if (inNote)
		print $0 >> "endnotes"
	else
		print
}
