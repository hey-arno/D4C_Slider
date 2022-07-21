*-- an update on this slick carousel*
*July 21, 2022*

Full details about Slick from http://kenwheeler.github.io/slick/
a running example (based on index) on the web can be found at https://arnoverhoeven.ca/degreeshow/

**Structure**
The root folder contains a folder for images and videos, as source for the slider.
The slick-1.8.1 folder (the package) contains everything that is required to run slick.  

**Contents**
There are a number of index_xxx files here:
- index_slickdemo_all.html -- the original Slick example code that contains all the possible sliders that this library can generate
- index_first.html --> this is the first attempt at sync-slider, pretty basic
- index_second.html --> bit more details, including actual images and background (drawn from /images folder)
- index_41slides.html --> expanding the first slider to see how the various CSS prefs work, and what 42 slides might look like
- index_video.html --> this contains actual images, and one video from /video folder (at slide 9) to see how embedded videos might work.  Page also has a header box for other assets (like Uni logo, etc)

**What to do**
Seb has an outline of three "pages" we require:  
- splashpage, which is activated after a timeout period
- slider page (see index examples above) which provides a carousel of "profile" student pages
- video page, more "personal" student focus which has their poster, bio and talking head video (the whole page is likely to be one video, compiled elsewhere and stored as .mp4, see index_video.html as example)

The whole system is driven by a custom "mouse" -- a rotary encoder that sends keystroke signals to the PC browser driving the site, making use of accessability features and keyboard driven navigation.  to that end, 
scrolling the encoder moves the navigation slider (left or right) using arrow keystrokes, and pressing the encoder "clicks" the focus area and launches the video -- return to slider when video is completed.  

These other details need to be figured out at .js level, but it seems Slick will allow this to work -- but that's what we need to do.




