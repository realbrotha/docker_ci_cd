      "  "'  (Æ   ÿÿÿÿÿÿ                  >   Cÿÿÿÿÿÿ   _   q            ¦ÿÿÿÿÿÿ      ·         Ð  ÿÿÿÿÿÿ   ð  "          Fÿÿÿÿÿÿ  ú        
  
1  úÿÿÿÿÿÿ       	     É  ¦ÿÿÿÿÿÿ  Ñ  ¬        ¡  ³ÿÿÿ     Ë  ÿÿÿÿÿÿ  Ã  !        E  $¾ÿÿÿÿÿÿ  y  %        ¥  %6ÿÿÿÿÿÿ  Ï  %_        î  %ÿÿÿÿÿÿ     %¦         '  %ãÿÿÿ      b  &.ÿÿÿÿÿÿ      &|         â  &Åÿÿÿÿÿÿ   è  &Ë         ù  &Ýÿÿÿÿÿÿ  !'  '#        !g  'ÿÿÿÿÿÿ  !  'ä         !Í  (2ÿÿÿ   !  !ñ  (fÿÿÿÿÿÿ  "  (usage: regconvert [-R alternate_root] [-f registry_file] [-b] registry conversion not required regconvert converted %d articles. out of memory could not create temporary directory for the registry conversion converting . . . %3d%% complete bad registry file %s Usage: prodreg unregister [-R <root>] (<mnemonic> <info> |
                                       [-fr] -u <uuid> -p <location>|
                                       [-fr] -u <uuid> -i <instance>)
This removes a component from the registry.
Caution is required when using the -r and -f options.

  <mnemonic>      An obsolete identifier for registered component types.
                  The mnemonic is really the 'unique name'attribute.
                  Components are unregistered recursively.
  <info>          An obsolete representation of install location, id attribute
                  or '-' wild card.
  -f              This forces the operation even if damage will result.
                  This option also unregisters all instances even if <uuid>
                  is ambiguous.
  -r              This causes a recursive unregistration of a  component
                  as well as that component's children and dependencies.
  -R <root>       An alternate root for the product registry database.
  -u <uuid>       This identifies a component type to unregister.
  -p <location>   This specifies the location of a component to unregister.
  -i <instance>   This specifies the instance of a component to unregister.

For more information, see prodreg(1M). Usage: prodreg uninstall ([-R <root>] <mnemonic> <info> [ARGS...] |
                          [-R <root>] [-f] -u <uuid> -p <location> [ARGS...] |
                          [-R <root>] [-f] -u <uuid> -i <instance> [ARGS...])
Launches an uninstaller referred to by a registered component or by its
absolution location.  Additional arguments are passed to the installer.
Uninstall will not be performed if it is determined that it would damage
a dependent component.

  <mnemonic>      An obsolete identifier for registered component types.
  <info>          An obsolete specifier of install location or id attribute.
  -f              This forces the operation even if damage will result.
  -u <uuid>       This identifies a component type to uninstall.
  -p <location>   This specifies the location of a component to uninstall.
  -i <instance>   This specifies the instance of a component to uninstall.
  -R <root>       An alternate root for the product registry database.
  ARGS            These arguments are passed to the uninstaller.

For more information, see prodreg(1M). Usage: prodreg swing [-R <root>]
This launches a Java Swing based prodreg graphical user interface.

  -R <root>       An alternate root for the product registry database.

For more information, see prodreg(1M). Usage: prodreg info [-R <root>] (-u <uuid> [-i <instance> | -p <location>] |
                                 -n <bnum> [-i <instance> | -p <location>] |
                                 -m <name> )]
                                  [(-a <attr> | -d )]
Display attribute information associated with a component in the Solaris
Install Registry.  All attributes are shown unless a specific attribute
name is requested, or '-d' queries whether the component is 'damaged.'
If a 'prodreg info' request is ambiguous, because the <uuid> or bnum given
refers to more than one instance, or because the <name> refers to more than one
component, the list of components which could have been referred to is
returned.

  -i <instance>   Specifies an installed instance of a component.
  -u <uuid>       Specifies a component to display info of.
  -m <name>       Gives the name of a component to display info of.
  -n <bnum>       Gives the number used to browse a component.
  -a <attr>       If given, return info on the specified attribute only.
  -d              If given, return only whether a component is damaged.
  -R <root>       An alternate root for the product registry database.

For more information, see prodreg(1M). Usage: prodreg browse [-R <root>] (-u <uuid> [-i <instance> | -p <location>] |
                                   -n <bnum> [-i <instance> | -p <location>] |
                                   -m <name> )]
Browse the Solaris Install Registry.  The ancestry of the component and
its children are listed, along with each components bnum, uuid,
instance number and name.  If a 'prodreg browse' request is ambiguous,
because the <uuid> given refers to more than one instance, or because
the <name> refers to more than one component, the list of components
which could have been referred to is returned.

Start by browsing the root of the Registry with "prodreg browse".  Select 
components to expand.  Use browse numbers as a convenience during this 
interactive browsing, but not in scripts, as they may change from one session 
to the next.  Browse numbers are generated as they are first used, for a given 
user on a particular system.

  -i <instance>   Browse the particular installed component instance.
  -u <uuid>       Browse the component with the given unique id.
  -m <name>       Browse the named component.
  -n <bnum>       Browse the component indicated by <bnum>.
  -R <root>       An alternate root for the product registry database.

For more information, see prodreg(1M). Usage: prodreg awt [-R <root>]
This launches a Java AWT based prodreg graphical user interface.

  -R <root>       An alternate root for the product registry database.

For more information, see prodreg(1M). Usage: prodreg SUBCOMMAND ARGUMENTS...
Administer and examine the Solaris Product Registry.
  prodreg [-R <root>]  Start the default prodreg GUI.
  prodreg awt          Start a Java awt GUI.
  prodreg browse       Browse the Registry.
  prodreg info         Examine the attributes of an entry in the Registry.
  prodreg help         Output this list.
  prodreg --help       Output this list.
  prodreg -?           Output this list.
  prodreg swing        Start a Java swing GUI.
  prodreg version      Output the version string.
  prodreg --version    Output the version string.
  prodreg -V           Output the version string.
  prodreg unregister   Unregister an entry in the registry.
  prodreg uninstall    Start an uninstaller registered with installed software.

For more information, see prodreg(1M). Usage: %s list [-R root] <fld> <fld> <fld> [<fld>...]
This is an archaic prodreg 2.0 command used to list attributes.
The attributes will only be listed if the attribute <fld> is 
supported by a particular component (with any value).

Each <fld> can be any of the following: 
    mnemonic    The unique name
    version     The version string
    vendor      The vendor string
    installlocation  The location
    title       The display name, as 'name' in prodreg cli.
    uninstallprogram  The location of the uninstaller.
    OTHER       Any additional attribute value.

Clean up scripts used 'prodreg list mnemonic mnemonic id'
There is no way to view the value of the UUID, aka 'id'.
Use 'prodreg info' and 'prodreg browse';  this feature is deprecated. Usage: %s SUBCOMMAND ARGUMENTS...
command subcommand arguments
prodreg            [-R altroot]
prodreg awt        [-R altroot]
prodreg browse     [-R altroot] -m <name>
prodreg browse     [-R altroot] -n <bnum>
prodreg browse     [-R altroot] [-u <uuid> [-i <instance>]]
prodreg --help
prodreg -?
prodreg info       [-R altroot] -n <bnum> [-R altroot] [(-a <attr> | -d)]
prodreg info       [-R altroot] -m <name> [(-a <attr> | -d)]
prodreg info       [-R altroot] -u <uuid> [-i <instance>] [(-a <attr>)| -d)]
prodreg swing      [-R altroot] 
prodreg uninstall  [-R altroot] [-f] -u <uuid> (-p <location> | -i <instance>) ARGS...
prodreg uninstall  [-R altroot] <mnemonic> <location> ARGS...
prodreg unregister [-R altroot] [-fr] -u <uuid> [(-p <location> | -i <instance>)]
prodreg unregister [-R altroot] <mnemonic> [<location>]
prodreg --version
prodreg -V

For more information, see prodreg(1M). The operation could not allocate sufficient memory. The component requested could not be found. The command line could not be understood. Parameter "%s" not understood. Initialization failed. Don't understand bad command "%s" Could not find prodreg GUI program: /usr/dt/bin/sdtprodreg Could not execute prodreg GUI program: /usr/dt/bin/sdtprodreg Could not determine the location of the prodreg GUI program file. 3.1.0 %s: No such file %s not converted: unrecognized return code %d %s not converted: the unzip binary is not installed in /usr/bin %s not converted: could not unzip the registry file %s %s not converted: Registry write access denied %s not converted: Permission denied %s %s System Software 
Use `prodreg --help` for help. ì¬ì©ë²:  regconvert [-R alternate_root] [-f registry_file] [-b] ë ì§ì¤í¸ë¦¬ ë³íì´ ìì²­ëì§ ìì regconvertê° %d í­ëª©ì¼ë¡ ë³íëììµëë¤. ë©ëª¨ë¦¬ ë¶ì¡± ë ì§ì¤í¸ë¦¬ ë³íì ìí ìì ëë í ë¦¬ë¥¼ ìì±í  ì ìì ë³í ì¤ . . . %3d%% ìë£ ìëª»ë ë ì§ì¤í¸ë¦¬ íì¼ %s ì¬ì©ë²: prodreg unregister [-R <ë£¨í¸>] (<ëëª¨ë> <ì ë³´> |
                                       [-fr] -u <uuid> -p <ìì¹>|
                                       [-fr] -u <uuid> -i <ì¸ì¤í´ì¤>)
ë ì§ì¤í¸ë¦¬ìì êµ¬ì± ììë¥¼ ì ê±°í©ëë¤.
-r ë° -f ìµìì ì¬ì©íë ê²½ì° ì£¼ìí´ì¼ í©ëë¤.

  <ëëª¨ë>        ë±ë¡ë êµ¬ì± ìì ì íì ëí ì´ì  ìë³ììëë¤.
                  ëëª¨ëì ì¤ì ë¡ 'ê³ ì í ì´ë¦'ìì±ìëë¤.
                  êµ¬ì± ììë ì¬ê·ì ì¼ë¡ ë±ë¡ì´ ì·¨ìë©ëë¤.
  <ì ë³´>          ì¤ì¹ ìì¹, ID ìì± ëë '-' ìì¼ëì¹´ëì
                  ì´ì  íììëë¤.
  -f              ììì´ ë°ìíë ê²½ì°ìë ììì ê°ì ë¡ ì¤íí©ëë¤.
                  ëí ì´ ìµìì <uuid>ê° ëª¨í¸í ê²½ì°ìë ëª¨ë  ì¸ì¤í´ì¤ì
                  ë±ë¡ì ì·¨ìí©ëë¤.
  -r              êµ¬ì± ììì ìì ë° ì¢ì ê´ê³ ììë¿ë§ ìëë¼
                  êµ¬ì± ììì ë±ë¡ì ì¬ê·ì ì¼ë¡ ì·¨ìí©ëë¤.
  -R <ë£¨í¸>       êµ¬ì± ìì ë ì§ì¤í¸ë¦¬ ë°ì´í°ë² ì´ì¤ì ëì²´ ë£¨í¸ìëë¤.
  -u <uuid>       ë±ë¡ì ì·¨ìí  êµ¬ì± ììì ì íì íì¸í©ëë¤.
  -p <ìì¹>       ë±ë¡ì ì·¨ìí  êµ¬ì± ììì ìì¹ë¥¼ ì§ì í©ëë¤.
  -i <ì¸ì¤í´ì¤>   ë±ë¡ì ì·¨ìí  êµ¬ì± ììì ì¸ì¤í´ì¤ë¥¼ ì§ì í©ëë¤.

ìì¸í ë´ì©ì prodreg(1M)ë¥¼ ì°¸ì¡°íì­ìì¤. ì¬ì©ë²: prodreg uninstall ([-R <ë£¨í¸>] <ëëª¨ë> <ì ë³´> [ì¸ì...] |
                          [-R <ë£¨í¸>] [-f] -u <uuid> -p <ìì¹> [ì¸ì...] |
                          [-R <ë£¨í¸>] [-f] -u <uuid> -i <ì¸ì¤í´ì¤> [ì¸ì...])
ë±ë¡ êµ¬ì± ìì ëë í´ë¹ ì ë ìì¹ì ìí´ ì°¸ì¡°ëë ì ê±° íë¡ê·¸ë¨ì
ììí©ëë¤. ì¶ê° ì¸ìë ì¤ì¹ íë¡ê·¸ë¨ì¼ë¡ ì ë¬ë©ëë¤.
ì¢ì êµ¬ì± ììë¥¼ ìììí¨ë¤ê³  íì¸ëë ê²½ì°ìë ì ê±°ê° ìíëì§
ììµëë¤.

  <ëëª¨ë>        ë±ë¡ë êµ¬ì± ìì ì íì ëí ì´ì  ìë³ììëë¤.
  <ì ë³´>          ì¤ì¹ ìì¹ ëë ID ìì±ì ëí ì´ì  ì§ì ììëë¤.
  -f              ììì´ ë°ìíë ê²½ì°ìë ììì ê°ì ë¡ ì¤íí©ëë¤.
  -u <uuid>       ì ê±°í  êµ¬ì± ììì ì íì íì¸í©ëë¤.
  -p <ìì¹>       ì ê±°í  êµ¬ì± ììì ìì¹ë¥¼ ì§ì í©ëë¤.
  -i <ì¸ì¤í´ì¤>   ì ê±°í  êµ¬ì± ììì ì¸ì¤í´ì¤ë¥¼ ì§ì í©ëë¤.
  -R <ë£¨í¸>       ì í ë ì§ì¤í¸ë¦¬ ë°ì´í°ë² ì´ì¤ì ëì²´ ë£¨í¸ìëë¤.
  ARGS            ì´ë¬í ì¸ìë ì ê±° íë¡ê·¸ë¨ì¼ë¡ ì ë¬ë©ëë¤.

ìì¸í ë´ì©ì prodreg(1M)ë¥¼ ì°¸ì¡°íì­ìì¤. ì¬ì©ë²: prodreg swing [-R <ë£¨í¸>]
Java Swing ê¸°ë° prodreg ê·¸ëí½ ì¬ì©ì ì¸í°íì´ì¤ë¥¼ ììí©ëë¤.

  -R <ë£¨í¸>       ì í ë ì§ì¤í¸ë¦¬ ë°ì´í°ë² ì´ì¤ì ëì²´ ë£¨í¸ìëë¤.

ìì¸í ë´ì©ì prodreg(1M)ë¥¼ ì°¸ì¡°íì­ìì¤. ì¬ì©ë²: prodreg info [-R <ë£¨í¸>] (-u <uuid> [-i <ì¸ì¤í´ì¤> | -p <ìì¹>] |
                                 -n <bnum> [-i <ì¸ì¤í´ì¤> | -p <ìì¹>] |
                                 -m <ì´ë¦> )]
                                  [(-a <ìì±> | -d )]
Solaris ì¤ì¹ ë ì§ì¤í¸ë¦¬ì êµ¬ì± ììì ê´ë ¨ë ìì± ì ë³´ë¥¼
íìí©ëë¤. í¹ì  ìì± ì´ë¦ì ìì²­íì§ ìì¼ë©´ ëª¨ë  ìì±ì´
íìë©ëë¤. ëë '-d'ë í¹ì  êµ¬ì± ììê° 'ìì'ëìëì§ ì¬ë¶ë¥¼ ì¡°íí©ëë¤.'
ì£¼ì´ì§ <uuid> ëë bnumì´ ë ê° ì´ìì ì¸ì¤í´ì¤ë¥¼ ì°¸ì¡°íê±°ë  <ì´ë¦>ì´
ë ê° ì´ìì êµ¬ì± ììë¥¼ ì°¸ì¡°íê¸° ëë¬¸ì 'prodreg info'
ìì²­ì´ ëª¨í¸í ê²½ì°, ì°¸ì¡°ë êµ¬ì± ìì ëª©ë¡ì´
ë°íë©ëë¤.

  -i <ì¸ì¤í´ì¤>   ì¤ì¹ë êµ¬ì± ììì ì¸ì¤í´ì¤ë¥¼ ì§ì í©ëë¤.
  -u <uuid>       í´ë¹ ì ë³´ë¥¼ íìí  êµ¬ì± ììë¥¼ ì§ì í©ëë¤.
  -m <ì´ë¦>       í´ë¹ ì ë³´ë¥¼ íìí  êµ¬ì± ììì ì´ë¦ì ì ê³µí©ëë¤.
  -n <bnum>       êµ¬ì± ììë¥¼ ê²ìíë ë° ì¬ì©ëë ë²í¸ë¥¼ ì ê³µí©ëë¤.
  -a <ìì±>       ì§ì ë ìì±ì ëí ì ë³´ë§ ë°íí©ëë¤.
  -d              êµ¬ì± ììê° ììëìëì§ ì¬ë¶ì ëí ì ë³´ë§ ë°íí©ëë¤.
  -R <ë£¨í¸>       ì í ë ì§ì¤í¸ë¦¬ ë°ì´í°ë² ì´ì¤ì ëì²´ ë£¨í¸ìëë¤.

ìì¸í ë´ì©ì prodreg(1M)ë¥¼ ì°¸ì¡°íì­ìì¤. ì¬ì©ë²: prodreg browse [-R <ë£¨í¸>] (-u <uuid> [-i <ì¸ì¤í´ì¤> | -p <ìì¹>] |
                                   -n <bnum> [-i <ì¸ì¤í´ì¤> | -p <ìì¹>] |
                                   -m <ì´ë¦> )]
Solaris ì¤ì¹ ë ì§ì¤í¸ë¦¬ë¥¼ ê²ìí©ëë¤.  êµ¬ì± ììì ìì/íì ê´ê³ê°
ê°ê°ì í´ë¹ bnum, uuid, ì¸ì¤í´ì¤ ë²í¸ ë° ì´ë¦ê³¼ í¨ê» 
ëì´ë©ëë¤. ì£¼ì´ì§ <uuid>ê° ë ê° ì´ìì 
ì¸ì¤í´ì¤ë¥¼ ì°¸ì¡°íê±°ë <ì´ë¦>ì´ ë ê° ì´ìì êµ¬ì± ììë¥¼ ì°¸ì¡°íê¸° ëë¬¸ì 'prodreg browse' ìì²­ì´ ëª¨í¸í ê²½ì°,
ì°¸ì¡°ë êµ¬ì± ìì ëª©ë¡ì´ ë°íë©ëë¤.

"prodreg browse"ë¡ ë ì§ì¤í¸ë¦¬ì ë£¨í¸ë¥¼ ê²ìíì¬ ììí©ëë¤.  íì¥í  
êµ¬ì± ììë¥¼ ì íí©ëë¤. ì´ ëíí ê²ì ì¤ìë í¸ìì ê²ì ë²í¸ë¥¼ ì¬ì©í©ëë¤. 
íì§ë§ ê²ì ë²í¸ë ì¸ì ê°ì ë³ê²½ë  ì ìì¼ë¯ë¡ ì¤í¬ë¦½í¸ììë ê²ì ë²í¸ë¥¼
ì¬ì©íì§ ììµëë¤. ê²ì ë²í¸ë í¹ì  ìì¤íì ì£¼ì´ì§ ì¬ì©ìì ëí´ ì²ìì¼ë¡ ì¬ì©ëë ê²½ì° 
ìì±ë©ëë¤.

  -i <ì¸ì¤í´ì¤>   ì¤ì¹ë í¹ì  ì¸ì¤í´ì¤ë¥¼ ê²ìí©ëë¤.
  -u <uuid>       ì£¼ì´ì§ ê³ ì í IDë¥¼ ì¬ì©íì¬ êµ¬ì± ììë¥¼ ê²ìí©ëë¤.
  -m <ì´ë¦>       ëªëªë êµ¬ì± ììë¥¼ ê²ìí©ëë¤.
  -n <bnum>       <bnum>ì ìí´ ì§ì ë êµ¬ì± ììë¥¼ ê²ìí©ëë¤.
  -R <ë£¨í¸>       ì í ë ì§ì¤í¸ë¦¬ ë°ì´í°ë² ì´ì¤ì ëì²´ ë£¨í¸ìëë¤.

ìì¸í ë´ì©ì prodreg(1M)ë¥¼ ì°¸ì¡°íì­ìì¤. ì¬ì©ë²: prodreg awt [-R <ë£¨í¸>]
Java AWT ê¸°ë° prodreg ê·¸ëí½ ì¬ì©ì ì¸í°íì´ì¤ë¥¼ ììí©ëë¤.

  -R <ë£¨í¸>       ì í ë ì§ì¤í¸ë¦¬ ë°ì´í°ë² ì´ì¤ì ëì²´ ë£¨í¸ìëë¤.

ìì¸í ë´ì©ì prodreg(1M)ë¥¼ ì°¸ì¡°íì­ìì¤. ì¬ì©ë²: prodreg íì ëªë ¹ì´ ì¸ì...
Solaris ì í ë ì§ì¤í¸ë¦¬ë¥¼ ê´ë¦¬íê³  íì¸í©ëë¤.
  prodreg [-R <ë£¨í¸>]  ê¸°ë³¸ prodreg GUIë¥¼ ììí©ëë¤.
  prodreg awt          Java awt GUIë¥¼ ììí©ëë¤.
  prodreg browse       ë ì§ì¤í¸ë¦¬ë¥¼ ê²ìí©ëë¤.
  prodreg info         ë ì§ì¤í¸ë¦¬ì í­ëª© ìì±ì íì¸í©ëë¤.
  prodreg help         ì´ ëª©ë¡ì ì¶ë ¥í©ëë¤.
  prodreg --help       ì´ ëª©ë¡ì ì¶ë ¥í©ëë¤.
  prodreg -?           ì´ ëª©ë¡ì ì¶ë ¥í©ëë¤.
  prodreg swing        Java swing GUIë¥¼ ììí©ëë¤.
  prodreg version      ë²ì  ë¬¸ìì´ì ì¶ë ¥í©ëë¤.
  prodreg --version    ë²ì  ë¬¸ìì´ì ì¶ë ¥í©ëë¤.
  prodreg -V           ë²ì  ë¬¸ìì´ì ì¶ë ¥í©ëë¤.
  prodreg unregister   ë ì§ì¤í¸ë¦¬ í­ëª©ì ë±ë¡ì ì·¨ìí©ëë¤.
  prodreg uninstall    ì¤ì¹ë ìíí¸ì¨ì´ì ë±ë¡ë ì ê±° íë¡ê·¸ë¨ì ììí©ëë¤.

ìì¸í ë´ì©ì prodreg(1M)ë¥¼ ì°¸ì¡°íì­ìì¤. ì¬ì©ë²: %s list [-R ë£¨í¸] <fld> <fld> <fld> [<fld>...]
ì´ê²ì ìì±ì ëì´íë ë° ì¬ì©íë ì´ì ì prodreg 2.0 ëªë ¹ì´ìëë¤.
ìì± <fld>ê° í¹ì  êµ¬ì± ìììì ì§ìëë ê²½ì°(ê°ì´ ìì)ìë§
í´ë¹ ìì±ì´ ëì´ë©ëë¤.

ê°ê°ì <fld>ë ë¤ì ì¤ íëì¼ ì ììµëë¤. 
    ëëª¨ë    ê³ ì í ì´ë¦
    ë²ì       ë²ì  ë¬¸ìì´
    ê³µê¸ìì²´  ê³µê¸ìì²´ ë¬¸ìì´
    ì¤ì¹ ìì¹ ìì¹
    ì ëª©      íì ì´ë¦(ì: prodreg cliì 'ì´ë¦').
    ì ê±° íë¡ê·¸ë¨  ì ê±° íë¡ê·¸ë¨ì ìì¹.
    ê¸°í      ëª¨ë  ì¶ê° ìì± ê°.

ì ë¦¬ ì¤í¬ë¦½í¸ìì 'prodreg list mnemonic mnemonic id'ë¥¼ ì¬ì©íìµëë¤.
UUID(ì¼ëª 'id') ê°ì ë³¼ ì ìë ë°©ë²ì´ ììµëë¤.
'prodreg info' ë° 'prodreg browse'ë¥¼ ì¬ì©íì­ìì¤.;  ì´ ê¸°ë¥ì ì¬ì©ëì§ ììµëë¤. ì¬ì©ë²: %s íì ëªë ¹ì´ ì¸ì...
ëªë ¹ì´    íì ëªë ¹ì´  ì¸ì
prodreg            [-R altroot]
prodreg awt        [-R altroot]
prodreg browse     [-R altroot] -m <ì´ë¦>
prodreg browse     [-R altroot] -n <bnum>
prodreg browse     [-R altroot] [-u <uuid> [-i <ì¸ì¤í´ì¤>]]
prodreg --help
prodreg -?
prodreg info       [-R altroot] -n <bnum> [-R altroot] [(-a <ìì±> | -d)]
prodreg info       [-R altroot] -m <ì´ë¦> [(-a <ìì±> | -d)]
prodreg info       [-R altroot] -u <uuid> [-i <ì¸ì¤í´ì¤>] [(-a <ìì±>)| -d)]
prodreg swing      [-R altroot] 
prodreg uninstall  [-R altroot] [-f] -u <uuid> (-p <ìì¹> | -i <ì¸ì¤í´ì¤>) ì¸ì...
prodreg uninstall  [-R altroot] <ëëª¨ë> <ìì¹> ì¸ì...
prodreg unregister [-R altroot] [-fr] -u <uuid> [(-p <ìì¹> | -i <ì¸ì¤í´ì¤>)]
prodreg unregister [-R altroot] <ëëª¨ë> [<ìì¹>]
prodreg --version
prodreg -V

ìì¸í ë´ì©ì prodreg(1M)ë¥¼ ì°¸ì¡°íì­ìì¤. ììì ìí ì¶©ë¶í ë©ëª¨ë¦¬ë¥¼ í ë¹í  ì ììµëë¤. ìì²­í êµ¬ì± ììë¥¼ ì°¾ì ì ììµëë¤. ëªë ¹ì¤ì ì´í´í  ì ììµëë¤. ë§¤ê°ë³ì "%s"ì(ë¥¼) ì´í´í  ì ììµëë¤. ì´ê¸°í ì¤í¨ ìëª»ë ëªë ¹ì´ "%s"ì(ë¥¼) ì´í´í  ì ììµëë¤. prodreg GUI íë¡ê·¸ë¨ì ì°¾ì ì ììµëë¤./usr/dt/bin/sdtprodreg prodreg GUI íë¡ê·¸ë¨ì ì¤íí  ì ììµëë¤./usr/dt/bin/sdtprodreg prodreg GUI íë¡ê·¸ë¨ íì¼ì ìì¹ë¥¼ íì¸í  ì ììµëë¤. 3.1.0 %s: íì¼ ìì %sì´(ê°) ë³íëì§ ìì: ì¸ìí  ì ìë ë°í ì½ë %d %sì´(ê°) ë³íëì§ ìì: ìì¶ í´ì  íë¡ê·¸ë¨ì´ /usr/binì ì¤ì¹ëì´ ìì§ ìì %sì´(ê°) ë³íëì§ ìì: ë ì§ì¤í¸ë¦¬ íì¼ %sì ìì¶ì í´ì í  ì ìì %sì´(ê°) ë³íëì§ ìì: ë ì§ì¤í¸ë¦¬ ì°ê¸° ì¡ì¸ì¤ê° ê±°ë¶ë¨ %sì´(ê°) ë³íëì§ ìì: ê¶íì´ ê±°ë¶ë¨ %s %s ìì¤í ìíí¸ì¨ì´ 
ëìë§ì ë³´ë ¤ë©´ `prodreg --help`ë¥¼ ì¬ì©íì­ìì¤. 