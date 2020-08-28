# Ortho-Mazes
A simple console program written in C++ for generating images of orthographic mazes.

This program was written in C++ for a class at university. It was not a class with a focus on object-oriented design or data-structures, but I felt like taking on this project anyway. I learned a lot about object-oriented programming and data structures along the way, and if you have the heart to delve into the source code you'll notice that despite the highly functional nature of the program, a number of serious reformations and optimizations could be made. As I am very interested in data structures, algorithms, graphics programming, and procedural generation, I look forward to incorporating the lessons I have learned into future project.

I wrote this project as a console application on Windows, for Windows. You can find an executable of the program here: https://github.com/dvanderweele/Ortho-Mazes/releases. 

You can literally do whatever you want with this program. However, being a school project, I'm not really considering making versions for Mac and Linux just because I have other priorities. However, nothing is stopping anyone else from forking this project and doing so. The main thing that I suspect would need to be changed to make this program compile for Mac or Linux is removal or changing of all the `system('cls')` calls that I sprinkled throughout the main file to make navigation of the crude console UI easier for the users. If you do fork this and make it compile for Mac and/or Linux, let me know and I'll drop a link to your repo or release on this page.

Furthermore, if you make any cool mazes with this program, let me know!

## FAQs

**Why did you use the .ppm file format? Isn't that ridiculous?**

Yes, it is ridiculous and highly inefficient, offering zero compression. However, I simply wanted a program that outputted maze images with zero external libraries incorporated and frankly the idea of trying to generate a png file without a library seems silly to me.

**What kind of mazes can you make with this?**

2D orthographic mazes that are built as a collection of square cells arranged in a grid. The walls are not lines, but simply "solid" or "filled" cells, whilst traversible corridors are "empty" or "carved". You can configure whether or not the maze is a weave maze, which means that corridors can tunnel beneath other corridors, as well as a host of other things like colors, size, loops, bias, etc.
