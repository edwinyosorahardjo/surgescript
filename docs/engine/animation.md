Animation
=========

Animation objects are used to gather data about specific animations. Although you can't spawn Animation objects directly, you can access them via other objects such as [Actor](/engine/actor) and [Player](/engine/player).

*Example*

```
using SurgeEngine.Actor;

object "MyExplosion" is "entity", "disposable", "private"
{
    actor = Actor("MyExplosion");

    state "main"
    {
        if(actor.animation.finished)
            destroy();
    }
}
```

Properties
----------

#### id

`id`: number.

The number of the current animation, defined in a .spr file.

#### sprite

`sprite`: string, read-only.

The name of the sprite, defined in a .spr file.

#### exists

`exists`: boolean, read-only.

Will be `true` if the current animation exists, i.e., if its sprite and its animation number have been defined in a .spr file.

*Available since:* Open Surge 0.5.1

#### finished

`finished`: boolean, read-only.

Will be `true` if the current animation has finished playing.

#### hotspot

`hotspot`: [Vector2](/engine/vector2) object, read-only.

The position of the hot spot of the current animation.

#### fps

`fps`: number, read-only.

Frames per second of the current animation.

#### repeats

`repeats`: boolean, read-only.

Does the current animation repeat itself?

#### frameCount

`frameCount`: number, read-only.

The number of frames of the current animation.

#### frame

`frame`: number.

The current frame of the animation: an integer between `0` and `frameCount - 1`, inclusive.

#### speedFactor

`speedFactor`: number.

While the [FPS](#fps) rate controls the speed of the animation, the speed factor gives you an additional degree of control. This is a multiplier that defaults to 1.0, meaning that the animation will run using its normal speed. If it's set to 2.0, it will run using twice that speed. A value of 0.5 means half the speed, and so on.

#### sync

`sync`: boolean.

Is the current animation is synchronized? A synchronized animation is a repeating animation that displays the same frame across multiple sprites. Defaults to `false`.