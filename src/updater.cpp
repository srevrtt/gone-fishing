// automatic update detector & updater

#include <iostream>
#include <string>
#include <Windows.h>
#include <filesystem>
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
    std::string line;

    std::getline(data, line);
    txt = line;

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
    system(cmd.c_str());
    finishedDownloading = true; // alert main.cpp that we finished downloading

    // rename the extracted file
    std::string renameCmd = "cd UpgradedVersion && rename GoneFishing_" + txt + " gone_fishing";

    system("cd UpgradedVersion && tar zxf gone_fishing.tar.gz");         // extract
    system(renameCmd.c_str());                                           // rename
    system("cd UpgradedVersion/gone_fishing && copy \"*.*\" ..");        // copy dlls and exe into the "UpgradedVersion" dir
    system("cd UpgradedVersion/gone_fishing && robocopy res ../res /e"); // copy "res" folder into the "UpgradedVersion" dir

    // cleanup
    system("cd UpgradedVersion && rd /S /Q gone_fishing && del gone_fishing.tar.gz");
    std::remove("data.txt");

    finishedUpdating = true; // alert main.cpp that upgrading is finished
}