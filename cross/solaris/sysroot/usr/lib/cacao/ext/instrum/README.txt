# Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# ident "$Revision: 1.8 $ SMI"
#


		+-----------------------------------+
		| Cacao self instrumentation README |
		+-----------------------------------+


1) Overview.

   The purpose of the instrumentation is to provide to the Cacao user
   information about activity inside the container and associated
   performance.
   
   The core of the instrumentation is packaged as a separated module inside
   an additional package 'SUNWcacaoinstr'.

   The instrumentation is available for Solaris and Linux on both platform
   Sparc and x86.

   Instrumentation data are exposed for :
   * Connectors data:
     - RMI   connectors
     - JMXMP connectors
     - Command Stream Adaptors
     - web service (if currently deployed inside the container)
     - module lock/unlock operations
     - module deploy/undeploy operations

   * Container data:
     - Deployed module count
     - Started module count
     - MBean count 
     - Max/Free/Total memory available for the JVM.

   Please notice that JMXMP connectors are now deprecated inside the 
   container.

   IMPORTANT MOTICE: 
   ================
        
   -------------------------------------------------------------------------
   A few items are still unfinished
   Please have a look to the TODO section to check for unavailable features
   -------------------------------------------------------------------------
  

   For any additional questions, please use the cacao dev team alias 

     cacao-dev@sun.com


2) Installation.
   
   The Instrumentation is delivered as part of cacao runtime package :
      On Solaris : SUNWcacao
      On Linux   : sun-cacao-1.1
   
   Packages layout is : 

      On Solaris

      <pkg base dir>/usr/lib/cacao/ext/instrum/etc/com.sun.cacao.instrum.xml
      <pkg base dir>/usr/lib/cacao/ext/instrum/lib/cacao_instrum.jar
      <pkg base dir>/usr/lib/cacao/ext/instrum/nbproject/project.xml

      On Linux
      
      <pkg base dir>/cacao/share/ext/instrum/etc/com.sun.cacao.instrum.xml
      <pkg base dir>/cacao/share/ext/instrum/lib/cacao_instrum.jar
      <pkg base dir>/cacao/share/ext/instrum/nbproject/project.xml


3) Deployment.

   Instrumentation activation is based on two parameters: 
		   - Instrumentation module
		   - Instrumentation flag set by cacaoadm set-param

   For this section we assume that the base dir of the cacao package
   and the cacao configuration package are respectively /usr/lib/cacao/ 
   and /etc/cacao/ - Please apply changes on paths according
   to your configuration
   

   Instrumentation inside the container must be activated before 
   container startup:
   
   This is done using the cacaoadm command : 

   /usr/lib/cacao/bin/cacaoadm set-param enable-instrumentation=true

   Setting this flag will have a negligable performance impact.

   The second Step is to deploy the instrumentation module. This can
   be done at Cacao startup or once Cacao is already running.
   
   - To activate the instrumentation at cacao start you must register 
     the deployment descriptor for startup time.

	/usr/lib/cacao/bin/cacaoadm register-module \  
		 /usr/lib/cacao/ext/instrum/etc/com.sun.cacao.instrum.xml
     
     Warning : the path to the jar file inside the xml file point by default to
	       the default install location of the JAR file.
	       If you relocate your package you should fix this

   - To activate the instrumentation at runtime you must use the
     'deploy' command of the cacaoadm administration script

     /usr/lib/cacao/bin/cacaoadm deploy \
		/usr/lib/cacao/ext/instrum/config/com.sun.cacao.instrum.xml

     Warning : cacao should have been started with the instrum flag
	       set to 'true' otherwise no instrumentation data will
	       be exposed 

4) Instrumentation and logs.

   Instrumentation
   ===============

   All instrumentation data is exposed by dedicated MBeans registered inside 
   the com.sun.cacao.instrum domain.
   
   For all details on MBeans exposed , please see the javadoc inside
   the sdk package. Here is a short description of available data


   Instrumentation data for a Cacao operations are exposed on a specific
   MBean.

   Instrumentation of the container are expose through the instrum MBean
   The pattern of this MBean is 

       int  DeployedModuleCount : number of module currently deployed inside the container
       int  StartedModuleCount  : number of module currently started inside the container
       int  MBeanCount          : number of MBean  currently registered inside the container
       long FreeMemory          : amount of free memory available for the vm	
       long MaxMemory           : maximum  memory available for the vm	
       long TotalMemory         : total amount of memory available for the vm	
       long StartDurationTime   : container start duration in nanoseconds

       void changeLogLevel(String) : change the log level of instrumentation logs

   Instrumentation data of container services such as lock, unlock, deploy, undeploy
   are exposed through the InstrumStat
   The pattern of this MBean is 

       long AbortedOperationsCount          : number of aborted operations.
       long FailedOperationsCount           : number of failed operations.
       long OperationsCount                 : number of operations
       
       long OperationsDurationTime          : time in nanosecond spend during successful operations
       long OperationsMaxDurationTime       :
				max time in nanosecond spend during successful operations
       long OperationsMinDurationTime       :
	                        min time in nanosecond spend during successful operations 
       double OperationsAverageDurationTime :
                                average in nanosecond spend during successful operations

       void resetStats	(void) : reset all statistics
   
   Instrumentation data of container connectors such as RMI, command stream etc.
   are exposed through the InstrumForwarderStat MBean which is a extension of InstrumStat
   MBean.
   Additional  pattern of this MBean is 
		int AuthenticationFailureCount : number of authentication failure
		Object[] Connections           : Set of all active connections
		int ConnectionsCount           : number of active connections
		int failedConnectionsCount     : number of connection failure


   IMPORTANT NOTICE:
     The connectors and adaptors expose the same statistics view.
     According to the type of monitored connector, instrumentation data may have
     a different meaning:
	     * AbortedOperationsCount statistics is only relevent for the command stream adaptor.
               For all others monitored connectors the counter remains to zero.
	     * For all connectors except for the command stream adaptor, an authentication failure
	       is only due to MBean access issue. Everything related to connection establishment is for now
	       (see 'TODO' section) only exposed by (included inside) the command stream adaptor
	       AuthenticationFailureCount statistic attribute.
		
   Logs:
   ====

   The log configuration is based on the log configuration of the
   container. the log file pattern is computed from the container log
   file pattern
   i.e : Cacao log file : /var/cacao/instances/default/logs/cacao.0
	 maps to instrum log file: /var/cacao/instances/default/logs/instrum-cacao.0

   A log record is compose of 4 fields separated by '>>' :	 
     - log time
     - log level
     - log record owner tag
     - log message

   example: 

     2005.02.07-17:07:20:690>>WARNING>>MODULE                                  >>Connector not monitored yet com.sun.cacao.webservices:t.......
     2005.02.07-17:07:20:710>>INFO   >>MODULE                                  >>public CommandStream stats not available yet
     2005.02.04-18:11:14:828>>FINEST >>CONNECTOR CACAO-RMI-WELLKNOWN           >>From Connection : <127.0.0.1:N/A>
     2005.02.04-18:11:14:829>>FINE   >>CONNECTOR CACAO-RMI-UNKNOWN             >>getAttribute <TotalMemory> on object name <com.sun.cacao.instrum:type=Instrum>

   
   Instrumentation loggers hierarchy is
		   com.sun.cacao.instrum
		   com.sun.cacao.instrum.core
		   com.sun.cacao.instrum.module
		   com.sun.cacao.instrum.lifecycle.locked
		   com.sun.cacao.instrum.lifecycle.unlocked
		   com.sun.cacao.instrum.command_stream.adaptor
		   com.sun.cacao.instrum.command_stream.shell
		   com.sun.cacao.instrum.connector.cacao-rmi-wellknown
		   com.sun.cacao.instrum.connector.cacao-rmi-unknown
		   com.sun.cacao.instrum.connector.cacao-jmxws-secure
		   com.sun.cacao.instrum.connector.jmxp

   log record owner tag are :
       - CONNECTOR JMXMP                  : log from a JMXMP connection
       - CONNECTOR CACAO-RMI-UNKNOWN      : log from a unknown mode RMI connection
       - CONNECTOR CACAO-RMI-WELLKNOWN    : log from a wellknown mode RMI connection
       - CONNECTOR COMMAND_STREAM ADAPTOR : log from a command stream adaptor connection
       - CONNECTOR COMMAND_STREAM SHELL   : log from a command stream command interpretor
       - CONNECTOR CACAO-JMXWS-SECURE     : log from a webservice connection
       - MODULE                           : log from the instrum module
       - CORE                             : log from the instrum module core
       - LIFECYCLE UNLOCKED               : log from an unlock operation
       - LIFECYCLE LOCKED                 : log from an lock operation
       

   NOTICE :
   * the user must not change log levels other than that of
     com.sun.cacao.instrum. The recommended way To do this is
     to invoke the 'changeLogLevel' method of the Instrum MBean
	   
   * According to the instrum log level, each request record is prefixed by the unique ID
     of the caller : fo instance : 'From Connection : <xxxx:xxxx>'. 
     Instrumentation use request' Subject to get this information. According to the type of connector
     the unique ID may have a different form: 
	 - for all connectors          : Unknown, the user ID is unknown (it may be the case for instance for webservices)
         - for all connectors          : Local, the request is an internal request performed by the MBean server itself
	 - for webservice connectors   : <N/A:HTTP session ID>
	 - for jmxmp connectors        : <host or IP:port>
	 - for rmi connectors          : <IP:N/A>
	 - for command stream adaptors : <host or IP:port>
   
5) Netbeans project.

    A Netbeans project is provided with the instrum module.
    It is possible to use it provided you have Netbeans 4.0 or higher
    and the Cacao Netbeans plugin installed (provided with Cacao SDK).
        
    The goal of this project is to enable you to use the runtime 
    features provided by the Cacao Netbeans plugin : deploy, undeploy,
    lock, unlock, status... with the instrum module.
    
    To open the Netbeans project, use the Netbeans open->project menu
    and navigate to the ./cacao/ext/instrum directory. 

6) TODO

   * the instrumentation flag is not yet completely dynamic : If you want to get instrumentation
     data please be sure that this flag is set to true inside the cacao.properties file
     and to start/stop instrumentation you need to deploy/undeploy the module 
     
   * JMX connectors authenticator may be instrumented (see CR 6247271)
   
