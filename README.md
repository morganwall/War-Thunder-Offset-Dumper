# War-Thunder-Offset-Dumper
A simple internal War Thunder sig scanner and offset dumper.
## Credit
Credit to [cazzwastaken](https://github.com/cazzwastaken) for the pattern scan function from his [crashed](https://github.com/cazzwastaken/crashed) repo.
I may rewrite it at somepoint, though I saw no reason to do so at the time.
## Dumping
### Addresses
- [x] Base
- [x] cGame
- [x] cLocalPlayer
- [x] cPlayerList
### Offsets
- [x] cGame
- [x] cLocalPlayer
- [x] cPlayerList

## Note
Please note that this project requires that EAC is disabled. Any attempt to use this with EAC enabled <b>WILL</b> most likely result in a permanent ban.
This project is also several months outdated, meaning that the signatures will need updating to work with the newest version of the game.
### Launching Without EAC
You can launch War Thunder without EAC using the standalone launcher, <code>launcher.exe</code>, which can be found in the War Thunder directory.
## Usage
### Cloning
Git is required in order to clone a github repository. You can find a download to git on their official website <a href="https://git-scm.com/">here</a>.
After installing git, open CMD and enter this command:
<pre><code>git clone https://github.com/morganwall/War-Thunder-Offset-Dumper.git</code></pre>
You should have now successfully cloned the repository.
### Requirements
This project was writen in Microsoft Visual Studio 2019 and may require platform toolset v142 or higher.
As the binary file is a DLL and the program is internal, you are required to use a DLL injector to inject the module into your game.
You can find a link to my LoadLibrary DLL Injector <a href="https://github.com/morganwall/LoadLibrary-DLL-Injector">here</a>.
This project was wrote and will only run on Windows.
### Compiling
First, please make sure that you have Microsoft Visual Studio 2019 intalled, along with platform toolset v142.
Open the .sln file included in the folder, with Microsoft Visual Studio 2019.
After that, change the build options to <code>Release | x64</code> and press Build.
Upon completion, you should recieve a binary called "War Thunder Offset Dumper.dll".
### Injecting
Before being able to inject, you need to launch War Thunder and login.
After launching the game, open your DLL injector, select the War Thunder process (<code>aces.exe</code>), select "War Thunder Offset Dumper.dll" and press inject.
Note: Injecting using my injector is slightly different, please see <a href="https://github.com/morganwall/LoadLibrary-DLL-Injector#operation">here</a> for instructions on how to inject using it.
Upon successfully injecting, a console window will appear containing the dumped offsets and addresses.
### License
<blockquote>Copyright (c) 2022 Morgan Wall</blockquote>
This project is licensed under the <a href="https://choosealicense.com/licenses/gpl-3.0/">GNU General Public License v3.0 License</a> - refer to the <a href="https://github.com/morganwall/War-Thunder-Offset-Dumper/blob/main/LICENSE">LICENSE</a> for more detail.
