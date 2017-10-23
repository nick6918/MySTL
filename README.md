# MySTL

## Repo Intro

This repo is to try to reconstruct an STL library that include all 6 core part of STL. This wiil be done in 5 major step:

      ### Step 1, Build Up all containers and data structures.
      
      Step 2, Build Up all algorithms works on one of the data structures selected.
      
      Step 3, Build Up all iterators we need, connect Algorithm and Container together by changing algorithm input from one data structure to one iterator.
      
      Step 4, Include adaptors and functors.
      
      Step 5, Working on memory optimization, include allocators.
      
<i>The Repo is currently at <b>1ST</b> step.</i> 
  
## File structure

all files in root content represents a mini project, introduced in the section below. All files in lib has been covered by these mini projects.

    --Containers

      Each file in this directory represent a container, those who start with an "_" should not be called directly from outside of thie directory or be exposed to users.
      
      The containers will be introduced in details in the next section.
      
    --Algorithms
    
      Each file in this directory represent an algorithm. Currently the input of those algorithm is one of the data structure we select from /Containers.
      
      The algorithms will be introduced in details in the coming section.
       
## Containers

The containers is listed here in a recommended reading sequence:


## Algorithms

## How to use

    1, Download the repo to local, a star to the repo is appreciated.
    
    2, make sure Python3 is installled in your local env, a virtual env is recommended.
    
    3, pip3 install -r requirements
    
    4, go to lib/datasets, manually run get_datasets.sh and get_3rd_data.sh to download dataset to local.
    
    5, feel free to run any project under root.

## More to do

I will implemented the following extra more model and project in very recent time.

[] DQN

[] RCNN

[] ResNet

## Special Thanks

This repo is heavily referenced with the assignment of cs231n. Special thanks to the great staff who gives us such a great online course materails.

Course link: http://cs231n.stanford.edu/

## Contact Me

Email: nick_fandingwei@outlook.com

Twitter: https://twitter.com/nick_fandingwei

For Chinese user, zhihu is the fastest way to get response from me: https://www.zhihu.com/people/NickWey

You can also check my tech blog for more: http://nickiwei.github.io/

Consider to follow me on Zhihu, Twitter and Github, thanks!
