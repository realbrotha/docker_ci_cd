/*
 * ident	"@(#)GuiResource.java	1.2	02/01/11 SMI"
 *
 * Copyright 2000-2002 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

import java.util.ListResourceBundle;

public class GuiResource extends ListResourceBundle {
    public Object[][] getContents() {
        return contents;
    }
    
    static final Object[][] contents = {
        {"Never", "Never"},
        {"Warning", "Warning"},
        {"Error", "Error"},
        {"Confirm Action", "Confirm Action"},
        {"Principals", "Principals"},
        {"Policies", "Policies"},
        {"Defaults", "Defaults"},
        {"Principal List", "Principal List"},
        {"Policy List", "Policy List"},
        {"Principal Basics", "Principal Basics"},
        {"Principal Details", "Principal Details"},
        {"Principal Flags", "Principal Flags"},
        {"Policy Details", "Policy Details" },
        {"Modify ", "Modify "},
        {"New ", "New "},
        {"Duplicate ", "Duplicate "},
        {"- *CHANGES*", "- *CHANGES*"},
        {"OK", "OK"},
        {"New", "New"},
        {"Please save or cancel first", "Please save or cancel first"},
        {"Cannot find default realm; check /etc/krb5/krb5.conf",
	 "Cannot find default realm; check /etc/krb5/krb5.conf"},
        {"Cannot find default server for realm",
	 "Cannot find default server for realm"},
        {"A password must be specified", "A password must be specified"},
        {"A realm entry must be specified",
	 "A realm entry must be specified"},
        {"A master KDC entry must be specified",
	 "A master KDC entry must be specified"},
        {"Invalid login, please try again",
	 "Invalid login, please try again"},
        {"Please enter a principal name or cancel",
	 "Please enter a principal name or cancel"},
        {"Please enter a password or cancel",
	 "Please enter a password or cancel"},
        {"Please enter a policy name or cancel",
	 "Please enter a policy name or cancel"},
        {"Context-Sensitive Help", "Context-Sensitive Help"},
        {"Click on GUI items to get help.\n\nClick on button below",
	 "to dismiss, Click on GUI items to get help.\n\nClick on",
	 "button below to dismiss"},
        {"Principal Name:", "Principal Name:"},
        {"Principal", "Principal"},
        {"Password:", "Password:"},
        {"Realm:", "Realm:"},
        {"Master KDC:", "Master KDC:"},
        {"Exit", "Exit"},
        {"About", "About"},
        {"Dismiss", "Dismiss"},
        {"Start Over", "Start Over"},
        {"Filter Pattern:", "Filter Pattern:"},
        {"Clear Filter", "Clear Filter"},
        {"Clear Name", "Clear Name"},
        {"Modify", "Modify"},
        {"Create New", "Create New"},
        {"Delete", "Delete"},
        {"Duplicate", "Duplicate"},
        {"General", "General"},
        {"Comments:", "Comments:"},
        {"Policy:", "Policy:"},
        {"Policy", "Policy"},
        {"Generate Random Password", "Generate Random Password"},
        {"Admin History", "Admin History"},
        {"Last Principal Change:", "Last Principal Change:"},
        {"Last Changed By:", "Last Changed By:"},
        {"Account Expires:", "Account Expires:"},
        {"Save", "Save"},
        {"Previous", "Previous"},
        {"Next", "Next"},
        {"Done", "Done"},
        {"Cancel", "Cancel"},
        {"Discard", "Discard"},
        {"Password", "Password"},
        {"Last Success:", "Last Success:"},
        {"Last Failure:", "Last Failure:"},
        {"Failure Count:", "Failure Count:"},
        {"Last Password Change:", "Last Password Change:"},
        {"Password Expires:", "Password Expires:"},
        {"Key Version:", "Key Version:"},
        {"Ticket Lifetimes", "Ticket Lifetimes"},
        {"Ticket", "Ticket"},
        {"Maximum Lifetime (seconds):",
	 "Maximum Lifetime (seconds):"},
        {"Maximum Renewal (seconds):",
	 "Maximum Renewal (seconds):"},
        {"Security", "Security"},
        {"Disable Account", "Disable Account"},
        {"Force Password Change", "Force Password Change"},
        {"Allow Postdated Tickets", "Allow Postdated Tickets"},
        {"Allow Forwardable Tickets", "Allow Forwardable Tickets"},
        {"Allow Renewable Tickets", "Allow Renewable Tickets"},
        {"Allow Proxiable Tickets", "Allow Proxiable Tickets"},
        {"Disallow Service Tickets", "Disallow Service Tickets"},
        {"Miscellaneous", "Miscellaneous"},
        {"Enforce Policy", "Enforce Policy"},
        {"Enable DES MD5", "Enable DES MD5"},
        {"Enable TGT-Based Authentication",
	 "Enable TGT-Based Authentication"},
        {"Enable Duplicate Authentication",
	 "Enable Duplicate Authentication"},
        {"Require Preauthentication", "Require Preauthentication"},
        {"Require Hardware Authentication",
	 "Require Hardware Authentication"},
        {"Policy Name:", "Policy Name:"},
        {"Minimum Password Length:", "Minimum Password Length:"},
        {"Minimum Password Classes:", "Minimum Password Classes:"},
        {"Saved Password History:", "Saved Password History:"},
        {"Minimum Ticket Lifetime (seconds):",
	 "Minimum Ticket Lifetime (seconds):"},
        {"Maximum Ticket Lifetime (seconds):",
	 "Maximum Ticket Lifetime (seconds):"},
        {"Maximum Ticket Renewal (seconds):",
	 "Maximum Ticket Renewal (seconds):"},
        {"Principals Using This Policy:", "Principals Using This Policy:"},
        {"Account Expiry:", "Account Expiry:"},
        {"Defaults for New Principals", "Defaults for New Principals"},
        {"Defaults for Existing Principals",
	 "Defaults for Existing Principals"},
        
        {"SEAM Date/Time Helper", "SEAM Date/Time Helper"},
        {"Month", "Month"},
        {"Date", "Date"},
        {"Year", "Year"},
        {"Hour", "Hour"},
        {"Minute", "Minute"},
        {"Second", "Second"},
        {"Now", "Now"},
        {"Midnight", "Midnight"},
        {"Help", "Help"},
        {"Help for Date and Time Dialog", "Help for Date and Time Dialog"},
        
        {"SEAM Duration Helper", "SEAM Duration Helper"},
        {"Weeks", "Weeks"},
        {"Unit", "Unit"},
        {"Value", "Value"},
        {"Seconds", "Seconds"},
        {"Minutes", "Minutes"},
        {"Hours", "Hours"},
        {"Days", "Days"},
        {"Weeks", "Weeks"},
        {"Months", "Months"},
        {"Years", "Years"},
        {"=", "="},
        {"Help for entering time duration",
	 "Help for entering time duration"},
        
        {"SEAM Print Helper", "SEAM Print Helper"},
        {"Print Command", "Print Command"},
        {"File Name", "File Name"},
        {"Print", "Print"},
        {"SEAM File Helper", "SEAM File Helper"},
        
        {"Reference Count:", "Reference Count:"},
        {"Minimum Password Lifetime (seconds):",
	 "Minimum Password Lifetime (seconds):"},
        {"Maximum Password Lifetime (seconds):",
	 "Maximum Password Lifetime (seconds):"},
        {"Password Save Count:", "Password Save Count:"},
        
        {"Flags:", "Flags:"},
        {"None", "None"},
        {"Allow Service Tickets", "Allow Service Tickets"},
        {"Allow TGT-Based Authentication",
	 "Allow TGT-Based Authentication"},
        {"Allow Duplicate Authentication",
	 "Allow Duplicate Authentication"},
        {"Allow Service Tickets", "Allow Service Tickets"},
        {"Require Preauthentication", "Require Preauthentication"},
        {"Require Hardware Preauthentication",
	 "Require Hardware Preauthentication"},
        {"Require Password Change", "Require Password Change"},
        {"Disallow Service", "Disallow Service"},
        {"Support DES MD5", "Support DES MD5"},
        {"Enforce Policy", "Enforce Policy"},
        {"(no policy)", "(no policy)"},
        {"Policy name already exists. Please choose a different",
	 "policy name or cancel",
	 "Policy name already exists. Please choose a different",
	 "policy name or cancel"},
        {"You are about to destroy data.",
	 "You are about to destroy data."},
        {"You are about to lose changes.",
	 "You are about to lose changes."},
        {"Click OK to proceed or Cancel to continue editing.",
	 "Click OK to proceed or Cancel to continue editing."},
        {"Click Save to commit changes, Discard to discard changes",
	 "or Cancel to continue editing.",
	 "Click Save to commit changes",
	 "Discard to discard changes, or Cancel",
	 "to continue editing."},
        {"Unable to access lists; please use the Name field.",
	 "Unable to access lists; please use the Name field."},
        {"About SEAM Adminstration Tool", "About SEAM Adminstration Tool"},
        {"Sun Enterprise Authentication Mechanism Administration Tool",
	 "Sun Enterprise Authentication Mechanism Administration",
	 "Tool"},
        {"Copyright 1999-2002 Sun Microsystems, Inc.",
	 "Copyright 1999-2002 Sun Microsystems, Inc."},
        {"All Rights Reserved.", "All Rights Reserved."},
        {"Example: ", "Example: "},
        {"or", "or"},
        {"Properties", "Properties"},
        {"List Controls", "List Controls"},
        {"Show Lists", "Show Lists"},
        {"Cache Lists Forever", "Cache Lists Forever"},
        {"List Cache Timeout (seconds):", "List Cache Timeout (seconds):"},
        {"Apply", "Apply"},
        {"Loading principal list", "Loading principal list"},
        {"Loading policy list", "Loading policy list"},
        {"File", "File"},
        {"Edit", "Edit"},
        {"Log Out", "Log Out"},
        {"Current Principal", "Current Principal"},
        {"Current Policy", "Current Policy"},
        {"Properties...", "Properties..."},
        {"Refresh", "Refresh"},
        {"Help Contents", "Help Contents"},
        {"Insufficient privileges to use gkadmin: ",
	 "Insufficient privileges to use gkadmin: "},
        {"Please try using another principal.",
	 "Please try using another principal."},
        {"Let the KDC control the ticket lifetime values",
	 "Let the KDC control the ticket lifetime values"},
        {"SEAM Administration Login", "SEAM Administration Login"},
        {"SEAM Administration Tool", "SEAM Administration Tool"},
        {"Can't run /usr/dt/bin/netscape.",
	 "Can't run /usr/dt/bin/netscape."},
        {"Invalid URL: ", "Invalid URL: "}
    };
}
