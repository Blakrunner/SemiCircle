# SemiCircle
Creating a semi circle using SFML

I created this file as I couldn't find anything easy to use with SFML.
The SemiCircle works with SFML and uses all Transforms. 

I've included a highlight color for added effect.

The SemiCircle can be used with default settings to draw a semi circle, an semi EllipseShape,
or you can use as follows:

SemiCircle semi;

SemiCircle ellipse(sf::Vector2f(50.f, 25.f));

or you can fully customize changing values as follows:

SemiCircle semiCircle(sf::Vector2f(size x radius, size y radius), start point, end point, number of points in full circle)


* March 13 2021 - Updated the update function.


[![image](https://github.com/Blakrunner/SemiCircle/blob/main/SemiCirclesample.png)]
