// automatic update detector & updater

#include <iostream>
#include <string>
#include <filesystem>
#include <Windows.h>
#include <fstream>

#include "include/updater.hpp"
std::string txt;

// update checker
bool Updater::check()
{
    const std::string currentVersion = "1.0.0-rc.2";

    // command to recieve latest version
    WinExec("curl -o data.txt https://raw.githubusercontent.com/srevrtt/gone-fishing/master/version.txt", SW_HIDE);

    // convert the version file into a string
    std::ifstream data("data.txt");
    std::string line, content;

    while (std::getline(data, line))
    {
        content += line;
    }

    txt = content;
    std::remove("data.txt");

    // if the release on the user's machine is not the latest version
    if (txt != currentVersion)
    {
        return true; // we want to update
    }

    return false; // we don't
}

// actual updating
void Updater::update(bool &finishedUpdating, bool &finishedDownloading)
{
    // command to recieve the latest release
    // (https://github.com/srevrtt/gone-fishing/releases/download/VERSION/VERSION.tar.gz)
    std::string file = "https://github.com/srevrtt/gone-fishing/releases/download/v" + txt + "/GoneFishing_" + txt + ".tar.gz";
    std::string cmd = "cd UpgradedVersion && certutil -urlcache -split -f " + file + " gone_fishing.tar.gz";

    // create a new directory with the updated game
    std::filesystem::create_directory("UpgradedVersion");

    // execute the file
    WinExec(cmd.c_str(), SW_HIDE);
    finishedDownloading = true; // alert main.cpp that we finished downloading

    // rename the extracted file
    std::string renameCmd = "cd UpgradedVersion && rename GoneFishing_" + txt + " gone_fishing";

    WinExec("cd UpgradedVersion && tar zxf gone_fishing.tar.gz", SW_HIDE);         // extract
    WinExec(renameCmd.c_str(), SW_HIDE);                                           // rename
    WinExec("cd UpgradedVersion/gone_fishing && copy \"*.*\" ..", SW_HIDE);        // copy dlls and exe into the "UpgradedVersion" dir
    WinExec("cd UpgradedVersion/gone_fishing && robocopy res ../res /e", SW_HIDE); // copy "res" folder into the "UpgradedVersion" dir

    // cleanup
    WinExec("cd UpgradedVersion && rd /S /Q gone_fishing && del gone_fishing.tar.gz", SW_HIDE);

    finishedUpdating = true; // alert main.cpp that upgrading is finished
}