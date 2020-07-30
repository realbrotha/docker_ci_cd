      "  "'   -   ��������                  >   @��������   _   `         �   ���������   �   �         �   ���������   �   �           ���������  �  �      
  
1  	R��������    
!   	     �  ���������  �          �  �����     �  ��������  �  �        E  %��������  y  U        �  z��������  �  �        �  ���������     �         '  �����      b  7��������   �  x         �  ���������   �  �         �  ���������  !'  �        !g  B��������  !�  �         !�  �����   !  !�  ���������  "  �usage: regconvert [-R alternate_root] [-f registry_file] [-b] registry conversion not required regconvert converted %d articles. out of memory could not create temporary directory for the registry conversion converting . . . %3d%% complete bad registry file %s Usage: prodreg unregister [-R <root>] (<mnemonic> <info> |
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
Use `prodreg --help` for help. ����:  regconvert [-R alternate_root] [-f registry_file] [-b] ������Ʈ�� ��ȯ�� ��û���� ���� regconvert�� %d �׸����� ��ȯ�Ǿ����ϴ�. �޸� ���� ������Ʈ�� ��ȯ�� ���� �ӽ� ���丮�� �ۼ��� �� ���� ��ȯ �� . . . %3d%% �Ϸ� �߸��� ������Ʈ�� ���� %s ����: prodreg unregister [-R <��Ʈ>] (<�ϸ��> <����> |
                                       [-fr] -u <uuid> -p <��ġ>|
                                       [-fr] -u <uuid> -i <�ν��Ͻ�>)
������Ʈ������ ���� ��Ҹ� �����մϴ�.
-r �� -f �ɼ��� ����ϴ� ��� �����ؾ� �մϴ�.

  <�ϸ��>        ��ϵ� ���� ��� ������ ���� ���� �ĺ����Դϴ�.
                  �ϸ���� ������ '������ �̸�'�Ӽ��Դϴ�.
                  ���� ��Ҵ� ��������� ����� ��ҵ˴ϴ�.
  <����>          ��ġ ��ġ, ID �Ӽ� �Ǵ� '-' ���ϵ�ī����
                  ���� ǥ���Դϴ�.
  -f              �ջ��� �߻��ϴ� ��쿡�� �۾��� ������ �����մϴ�.
                  ���� �� �ɼ��� <uuid>�� ��ȣ�� ��쿡�� ��� �ν��Ͻ���
                  ����� ����մϴ�.
  -r              ���� ����� �ڽ� �� ���� ���� ��һӸ� �ƴ϶�
                  ���� ����� ����� ��������� ����մϴ�.
  -R <��Ʈ>       ���� ��� ������Ʈ�� �����ͺ��̽��� ��ü ��Ʈ�Դϴ�.
  -u <uuid>       ����� ����� ���� ����� ������ Ȯ���մϴ�.
  -p <��ġ>       ����� ����� ���� ����� ��ġ�� �����մϴ�.
  -i <�ν��Ͻ�>   ����� ����� ���� ����� �ν��Ͻ��� �����մϴ�.

�ڼ��� ������ prodreg(1M)�� �����Ͻʽÿ�. ����: prodreg uninstall ([-R <��Ʈ>] <�ϸ��> <����> [�μ�...] |
                          [-R <��Ʈ>] [-f] -u <uuid> -p <��ġ> [�μ�...] |
                          [-R <��Ʈ>] [-f] -u <uuid> -i <�ν��Ͻ�> [�μ�...])
��� ���� ��� �Ǵ� �ش� ���� ��ġ�� ���� �����Ǵ� ���� ���α׷���
�����մϴ�. �߰� �μ��� ��ġ ���α׷����� ���޵˴ϴ�.
���� ���� ��Ҹ� �ջ��Ų�ٰ� Ȯ�εǴ� ��쿡�� ���Ű� �������
�ʽ��ϴ�.

  <�ϸ��>        ��ϵ� ���� ��� ������ ���� ���� �ĺ����Դϴ�.
  <����>          ��ġ ��ġ �Ǵ� ID �Ӽ��� ���� ���� �������Դϴ�.
  -f              �ջ��� �߻��ϴ� ��쿡�� �۾��� ������ �����մϴ�.
  -u <uuid>       ������ ���� ����� ������ Ȯ���մϴ�.
  -p <��ġ>       ������ ���� ����� ��ġ�� �����մϴ�.
  -i <�ν��Ͻ�>   ������ ���� ����� �ν��Ͻ��� �����մϴ�.
  -R <��Ʈ>       ��ǰ ������Ʈ�� �����ͺ��̽��� ��ü ��Ʈ�Դϴ�.
  ARGS            �̷��� �μ��� ���� ���α׷����� ���޵˴ϴ�.

�ڼ��� ������ prodreg(1M)�� �����Ͻʽÿ�. ����: prodreg swing [-R <��Ʈ>]
Java Swing ��� prodreg �׷��� ����� �������̽��� �����մϴ�.

  -R <��Ʈ>       ��ǰ ������Ʈ�� �����ͺ��̽��� ��ü ��Ʈ�Դϴ�.

�ڼ��� ������ prodreg(1M)�� �����Ͻʽÿ�. ����: prodreg info [-R <��Ʈ>] (-u <uuid> [-i <�ν��Ͻ�> | -p <��ġ>] |
                                 -n <bnum> [-i <�ν��Ͻ�> | -p <��ġ>] |
                                 -m <�̸�> )]
                                  [(-a <�Ӽ�> | -d )]
Solaris ��ġ ������Ʈ���� ���� ��ҿ� ���õ� �Ӽ� ������
ǥ���մϴ�. Ư�� �Ӽ� �̸��� ��û���� ������ ��� �Ӽ���
ǥ�õ˴ϴ�. �Ǵ� '-d'�� Ư�� ���� ��Ұ� '�ջ�'�Ǿ����� ���θ� ��ȸ�մϴ�.'
�־��� <uuid> �Ǵ� bnum�� �� �� �̻��� �ν��Ͻ��� �����ϰų�  <�̸�>��
�� �� �̻��� ���� ��Ҹ� �����ϱ� ������ 'prodreg info'
��û�� ��ȣ�� ���, ������ ���� ��� �����
��ȯ�˴ϴ�.

  -i <�ν��Ͻ�>   ��ġ�� ���� ����� �ν��Ͻ��� �����մϴ�.
  -u <uuid>       �ش� ������ ǥ���� ���� ��Ҹ� �����մϴ�.
  -m <�̸�>       �ش� ������ ǥ���� ���� ����� �̸��� �����մϴ�.
  -n <bnum>       ���� ��Ҹ� �˻��ϴ� �� ���Ǵ� ��ȣ�� �����մϴ�.
  -a <�Ӽ�>       ������ �Ӽ��� ���� ������ ��ȯ�մϴ�.
  -d              ���� ��Ұ� �ջ�Ǿ����� ���ο� ���� ������ ��ȯ�մϴ�.
  -R <��Ʈ>       ��ǰ ������Ʈ�� �����ͺ��̽��� ��ü ��Ʈ�Դϴ�.

�ڼ��� ������ prodreg(1M)�� �����Ͻʽÿ�. ����: prodreg browse [-R <��Ʈ>] (-u <uuid> [-i <�ν��Ͻ�> | -p <��ġ>] |
                                   -n <bnum> [-i <�ν��Ͻ�> | -p <��ġ>] |
                                   -m <�̸�> )]
Solaris ��ġ ������Ʈ���� �˻��մϴ�.  ���� ����� ����/���� ���谡
������ �ش� bnum, uuid, �ν��Ͻ� ��ȣ �� �̸��� �Բ� 
�����˴ϴ�. �־��� <uuid>�� �� �� �̻��� 
�ν��Ͻ��� �����ϰų� <�̸�>�� �� �� �̻��� ���� ��Ҹ� �����ϱ� ������ 'prodreg browse' ��û�� ��ȣ�� ���,
������ ���� ��� ����� ��ȯ�˴ϴ�.

"prodreg browse"�� ������Ʈ���� ��Ʈ�� �˻��Ͽ� �����մϴ�.  Ȯ���� 
���� ��Ҹ� �����մϴ�. �� ��ȭ�� �˻� �߿��� ���ǻ� �˻� ��ȣ�� ����մϴ�. 
������ �˻� ��ȣ�� ���� ���� ����� �� �����Ƿ� ��ũ��Ʈ������ �˻� ��ȣ��
������� �ʽ��ϴ�. �˻� ��ȣ�� Ư�� �ý����� �־��� ����ڿ� ���� ó������ ���Ǵ� ��� 
�����˴ϴ�.

  -i <�ν��Ͻ�>   ��ġ�� Ư�� �ν��Ͻ��� �˻��մϴ�.
  -u <uuid>       �־��� ������ ID�� ����Ͽ� ���� ��Ҹ� �˻��մϴ�.
  -m <�̸�>       ������ ���� ��Ҹ� �˻��մϴ�.
  -n <bnum>       <bnum>�� ���� ������ ���� ��Ҹ� �˻��մϴ�.
  -R <��Ʈ>       ��ǰ ������Ʈ�� �����ͺ��̽��� ��ü ��Ʈ�Դϴ�.

�ڼ��� ������ prodreg(1M)�� �����Ͻʽÿ�. ����: prodreg awt [-R <��Ʈ>]
Java AWT ��� prodreg �׷��� ����� �������̽��� �����մϴ�.

  -R <��Ʈ>       ��ǰ ������Ʈ�� �����ͺ��̽��� ��ü ��Ʈ�Դϴ�.

�ڼ��� ������ prodreg(1M)�� �����Ͻʽÿ�. ����: prodreg ���� ���ɾ� �μ�...
Solaris ��ǰ ������Ʈ���� �����ϰ� Ȯ���մϴ�.
  prodreg [-R <��Ʈ>]  �⺻ prodreg GUI�� �����մϴ�.
  prodreg awt          Java awt GUI�� �����մϴ�.
  prodreg browse       ������Ʈ���� �˻��մϴ�.
  prodreg info         ������Ʈ���� �׸� �Ӽ��� Ȯ���մϴ�.
  prodreg help         �� ����� ����մϴ�.
  prodreg --help       �� ����� ����մϴ�.
  prodreg -?           �� ����� ����մϴ�.
  prodreg swing        Java swing GUI�� �����մϴ�.
  prodreg version      ���� ���ڿ��� ����մϴ�.
  prodreg --version    ���� ���ڿ��� ����մϴ�.
  prodreg -V           ���� ���ڿ��� ����մϴ�.
  prodreg unregister   ������Ʈ�� �׸��� ����� ����մϴ�.
  prodreg uninstall    ��ġ�� ����Ʈ��� ��ϵ� ���� ���α׷��� �����մϴ�.

�ڼ��� ������ prodreg(1M)�� �����Ͻʽÿ�. ����: %s list [-R ��Ʈ] <fld> <fld> <fld> [<fld>...]
�̰��� �Ӽ��� �����ϴ� �� ����ϴ� ������ prodreg 2.0 ���ɾ��Դϴ�.
�Ӽ� <fld>�� Ư�� ���� ��ҿ��� �����Ǵ� ���(���� ����)����
�ش� �Ӽ��� �����˴ϴ�.

������ <fld>�� ���� �� �ϳ��� �� �ֽ��ϴ�. 
    �ϸ��    ������ �̸�
    ����      ���� ���ڿ�
    ���޾�ü  ���޾�ü ���ڿ�
    ��ġ ��ġ ��ġ
    ����      ǥ�� �̸�(��: prodreg cli�� '�̸�').
    ���� ���α׷�  ���� ���α׷��� ��ġ.
    ��Ÿ      ��� �߰� �Ӽ� ��.

���� ��ũ��Ʈ���� 'prodreg list mnemonic mnemonic id'�� ����߽��ϴ�.
UUID(�ϸ� 'id') ���� �� �� �ִ� ����� �����ϴ�.
'prodreg info' �� 'prodreg browse'�� ����Ͻʽÿ�.;  �� ����� ������ �ʽ��ϴ�. ����: %s ���� ���ɾ� �μ�...
���ɾ�    ���� ���ɾ�  �μ�
prodreg            [-R altroot]
prodreg awt        [-R altroot]
prodreg browse     [-R altroot] -m <�̸�>
prodreg browse     [-R altroot] -n <bnum>
prodreg browse     [-R altroot] [-u <uuid> [-i <�ν��Ͻ�>]]
prodreg --help
prodreg -?
prodreg info       [-R altroot] -n <bnum> [-R altroot] [(-a <�Ӽ�> | -d)]
prodreg info       [-R altroot] -m <�̸�> [(-a <�Ӽ�> | -d)]
prodreg info       [-R altroot] -u <uuid> [-i <�ν��Ͻ�>] [(-a <�Ӽ�>)| -d)]
prodreg swing      [-R altroot] 
prodreg uninstall  [-R altroot] [-f] -u <uuid> (-p <��ġ> | -i <�ν��Ͻ�>) �μ�...
prodreg uninstall  [-R altroot] <�ϸ��> <��ġ> �μ�...
prodreg unregister [-R altroot] [-fr] -u <uuid> [(-p <��ġ> | -i <�ν��Ͻ�>)]
prodreg unregister [-R altroot] <�ϸ��> [<��ġ>]
prodreg --version
prodreg -V

�ڼ��� ������ prodreg(1M)�� �����Ͻʽÿ�. �۾��� ���� ����� �޸𸮸� �Ҵ��� �� �����ϴ�. ��û�� ���� ��Ҹ� ã�� �� �����ϴ�. �������� ������ �� �����ϴ�. �Ű����� "%s"��(��) ������ �� �����ϴ�. �ʱ�ȭ ���� �߸��� ���ɾ� "%s"��(��) ������ �� �����ϴ�. prodreg GUI ���α׷��� ã�� �� �����ϴ�./usr/dt/bin/sdtprodreg prodreg GUI ���α׷��� ������ �� �����ϴ�./usr/dt/bin/sdtprodreg prodreg GUI ���α׷� ������ ��ġ�� Ȯ���� �� �����ϴ�. 3.1.0 %s: ���� ���� %s��(��) ��ȯ���� ����: �ν��� �� ���� ��ȯ �ڵ� %d %s��(��) ��ȯ���� ����: ���� ���� ���α׷��� /usr/bin�� ��ġ�Ǿ� ���� ���� %s��(��) ��ȯ���� ����: ������Ʈ�� ���� %s�� ������ ������ �� ���� %s��(��) ��ȯ���� ����: ������Ʈ�� ���� �׼����� �źε� %s��(��) ��ȯ���� ����: ������ �źε� %s %s �ý��� ����Ʈ���� 
������ ������ `prodreg --help`�� ����Ͻʽÿ�. 