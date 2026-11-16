# Discovery report

## Problem statement

The client needs a ray tracer it can trust and maintain for years, because AI-generated code is easy to produce but hard to understand, but rendering tools built this way keep breaking with no one able to fix them.

## Client interview summary

### Speed and deadline

**Need:** The client wants the ray tracer to render fast, especially for a full movie with many frames.

> **Q (us):** "What is a reasonable render time for you?"
>
> **A:** "Very fast."

> **Q (us):** "How many frames per second do you need?"
>
> **A:** "24 frames per second."

> **Q (us):** "How long is the movie usually?"
>
> **A:** "90 minutes."

> **Q (us):** "What is your deadline for this project?"
>
> **A:** "Two months."

**My conclusion:** A 90-minute movie at 24 frames per second needs about 130,000 frames. The deadline is short (2 months). This means speed is very important for this project.

### Image quality

**Need:** The client wants realistic images for the final scenes.

> **Q (us):** "What is more important: realistic images, or fast images?"
>
> **A:** "For the final scene, the most realistic image is important."

**My conclusion:** Quality is more important than speed for the final render. This may create a conflict with the short deadline (see Open questions).

### Contributions from partner studios

**Need:** Other studios must be able to use and understand the code.

> **Q (us):** "Do other studios use the same programming language?"
>
> **A:** "Yes, C++."

> **Q (us):** "Do you have rules or a style guide for the code?"
>
> **A:** "No."

> **Q (us):** "Do you need documentation in a special format?"
>
> **A:** "No."

> **Q (us):** "Who will read the documentation?"
>
> **A:** "Developers."

> **Q (us):** "Do you use a specific tool to manage code, like Git?"
>
> **A:** "No."

**My conclusion:** We can write the documentation for developers, in a normal, simple way. We do not need to follow a special style guide.

### 3D software

**Need:** The ray tracer must work with the 3D scenes made by the artists.

> **Q (us):** "What software do your artists use to create 3D scenes?"
>
> **A:** "Maya."

> **Q (us):** "Do you need the ray tracer to connect directly to that software, or can it read a file instead?"
>
> **A:** "Read a file."

> **Q (us):** "Is there a standard file format we should support?"
>
> **A:** "We can decide it."

**My conclusion:** We do not need a plugin inside Maya. We only need to read a file exported from Maya. We can choose the file format ourselves.

### Open questions

- The client wants images that are very realistic, but also wants a very fast render, in only 2 months. These two goals can be hard to reach together. We need to check if this is possible.
- The client said "no" to using Git, but this is unusual for a team project. We should ask again, or decide this ourselves.
- We did not get a clear answer about budget or computer power for the final rendering (on the client's side).

## State of the art

| Solution | Maker | Licence | Pricing (date checked) | Capabilities | Sources |
|---|---|---|---|---|---|
| pbrt | Matt Pharr, Wenzel Jakob, Greg Humphreys (research project, book "Physically Based Rendering") | Open source (BSD licence) | Free | Physically based ray tracer, written in C++, full source code and full book text available online, built for teaching and research | [pbrt.org](https://pbrt.org), [pbr-book.org](https://pbr-book.org/4ed/Introduction) (checked Nov 2026) |
| Blender Cycles | Blender Foundation | Open source (Apache License 2.0; Blender itself is GPL) | Free | Physically based path tracer, GPU rendering (CUDA, OptiX, HIP, Metal), built into Blender, usable outside Blender too because of its permissive licence | [code.blender.org](https://code.blender.org/2013/08/cycles-render-engine-released-with-permissive-license/), [blender.org](https://www.blender.org/?p=658) (checked Nov 2026) |
| Autodesk Arnold | Autodesk | Commercial (paid subscription) | About $430–$600 per year for one user, depending on the reseller | Monte Carlo ray tracer, used for complex VFX and movies, connects to Maya and 3ds Max | [autodesk.com/arnold](https://www.autodesk.com/arnold) (official product page), [cdwg.com](https://www.cdwg.com/product/arnold-2026-new-subscription-annual-5-seats/9115347) (checked Nov 2026) |
| Chaos V-Ray | Chaos Group | Commercial (paid subscription) | V-Ray Solo: $540/year or $45/month (official price) | Production renderer, works with many 3D tools, supports CPU and GPU rendering | [chaos.com/vray/buy-online](https://www.chaos.com/vray/buy-online) (official pricing page, checked Nov 2026) |

**What we conclude:** All four solutions are fast enough and realistic enough for real studio work, so that is not the gap. The gap is **who can read and change the code**. Arnold and V-Ray are commercial and closed: the client cannot read, maintain, or extend their source code, even though the client's own need is exactly that (a ray tracer "it can trust, maintain and extend for years"). pbrt and Blender Cycles are open and readable, which is closer to what the client wants, but pbrt is a teaching tool, not built for a short production deadline, and Cycles is built to live inside Blender, not as a separate, studio-owned tool open to partner studios. So none of the four solutions fully matches what the client asked for: open, readable C++ source, owned and extendable by the client and its partners, fast enough for a full film. This confirms why the client needs a team to build one, instead of buying or reusing an existing ray tracer.

## What is ray tracing?

Ray tracing is a way to make 3D images by following light. The computer sends out virtual light rays, one for each pixel of the image. It checks what each ray touches in the 3D scene. Then it calculates the color of that point, using how light bounces, reflects, and creates shadows. This method can make very realistic images, close to a real photo, because it copies how light moves in the real world. It takes more time to calculate than other, simpler methods, because the computer must follow many rays and many bounces of light.

**Sources:** We started from the official NVIDIA page "Ray Tracing Essentials" (developer.nvidia.com/discover/ray-tracing), and from pbrt's own book, "Physically Based Rendering: From Theory to Implementation", 4th edition, whose full text is free online since November 2023 (pbr-book.org/4ed), which we will come back to for the technical details of our implementation.

## What is C++?

### Programming paradigms

C++ is a multi-paradigm language: it supports procedural code, object-oriented code (classes), generic code (templates), and some functional-style code. We already know JavaScript, which is also multi-paradigm (it supports object-oriented, procedural, and functional styles). So both languages let us mix styles instead of forcing only one.

The real difference is typing. JavaScript is dynamically typed: a variable can change type at any time, and the type is only checked while the program runs. C++ is statically typed: every variable's type is fixed and checked before the program even runs (at compile time). This also changes what "generic code" means: in JavaScript, a function just works with whatever type you give it, with no extra step. In C++, writing code that works with many types needs templates, which are resolved at compile time, not at runtime.

### What to watch out for

JavaScript handles memory for us automatically, with a garbage collector: objects we stop using are found and removed by the language itself. C++ does not do this. We must create and destroy objects ourselves (or use tools like smart pointers that do it for us in a safer way). If we forget, we get memory leaks (memory that is never freed) or crashes (using memory that was already freed).

C++ also lets us make mistakes that JavaScript simply does not allow. For example, reading past the end of an array in JavaScript gives `undefined`; in C++, this can silently corrupt memory instead of showing a clear error. This kind of mistake is called "undefined behavior," and it is one of the classic traps of C++: the program may seem to work, then fail later, somewhere else, for no clear reason.

### Shaping the domain model

In JavaScript, we could build our domain model (scene, shapes, rays, materials, camera) with plain objects, and never think about memory, because the language manages it for us. In C++, because memory is not automatic, we must decide, for every object, who owns it and who is responsible for deleting it. We plan to represent shapes, materials and lights as separate classes, using inheritance so partner studios can add new shapes or materials without touching the core code, and using templates where the same logic must work for different numeric types. This means more design decisions up front than in JavaScript: our classes must be clear not just about what data they hold, but about who owns that data and for how long.

**Sources:** We started from the official MDN JavaScript documentation (developer.mozilla.org/en-US/docs/Web/JavaScript), which describes JavaScript as a prototype-based, multi-paradigm, dynamic, garbage-collected language, and from cppreference.com, the main online reference for the C++ language, which we will keep using as our reference while writing the code.