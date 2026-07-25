<p align="center">
  <a href="https://get.blackblox.com">
    <img src="docs/images/hero-clock.png" alt="BLACKBLOX modular 48 x 16 matrix clock" width="100%">
  </a>
</p>

<h1 align="center">BLACKBLOX SDK</h1>

<p align="center">
  <strong>From idea to working hardware in minutes.</strong><br>
  <strong>Create products. Not prototypes.</strong>
</p>

<p align="center">
  <a href="https://get.blackblox.com"><strong>Website</strong></a>
  &nbsp;•&nbsp;
  <a href="docs/GETTING_STARTED.md"><strong>Getting started</strong></a>
  &nbsp;•&nbsp;
  <a href="docs/INSTALLATION.md"><strong>Installation</strong></a>
  &nbsp;•&nbsp;
  <a href="docs/FIRST_PROJECT.md"><strong>First project</strong></a>
</p>

> The clock above was built by connecting an ESP processor cube and six BLACKBLOX RGB matrix cubes. No application-specific PCB was required.

BLACKBLOX is an open-source modular electronics platform for building real products from reusable intelligent cubes.

Connect cubes. Write code. Build the product your customer actually needs.

---

## Every product starts with an idea

Some ideas become products. Most never do.

Not because they are not good enough, but because building hardware takes too long.

Design. Prototype. Wait. Fix. Repeat.

Weeks become months. Momentum fades. Requirements change. Opportunities disappear.

BLACKBLOX was created to shorten that journey. Instead of starting from scratch, you assemble hardware blocks that already work together and spend your time improving the product rather than repeatedly rebuilding the electronics.

---

## Why BLACKBLOX?

| Traditional development | Typical time | BLACKBLOX | Typical time |
|---|---:|---|---:|
| New idea | Day 0 | New idea | Day 0 |
| Design a PCB | 1–2 weeks | Connect cubes | 5 min |
| Order prototypes | 1 week | Open an example | 2 min |
| Manufacturing and delivery | 1–2 weeks | Start programming | 10 min |
| Assemble and test | 1 day | First hardware test | 1 min |
| Something does not work | — | Something does not work | — |
| Redesign the PCB | 1 week | Change the software | 2 min |
| Order another revision | 1 week | Add or replace a cube | 2 min |
| Wait again | 1–2 weeks | Continue developing | Immediately |
| Build everything again | Several weeks | Continue improving the product | Immediately |
| **Repeat until the hardware finally works** | **Weeks or months** | **Repeat until your customer is happy** | **Minutes** |

Traditional development spends too much time waiting: for PCBs, components, delivery and the next revision.

BLACKBLOX lets you spend that time testing ideas with users and adapting the product until it is right.

---

## Build instead of redesign

Every BLACKBLOX cube has a purpose:

- processor cubes,
- display cubes,
- sensor cubes,
- touch and control cubes,
- communication cubes,
- power cubes.

Need another display? Add a display cube.

Need environmental data? Connect sensor cubes.

Need more processing power or computer vision? Add a Raspberry Pi processor and camera.

Your hardware can grow with the idea while the application remains understandable and reusable.

---

## Hello BLACKBLOX

```cpp
#include <BLACKBLOX.h>

using namespace blackblox;

BBRGBMatrix8x16 matrix(0x11);

void setup()
{
    BB.begin();
    matrix.begin();

    matrix.fill(BBColor::Blue);
    matrix.show();
}

void loop()
{
}
```

That is enough to initialize BLACKBLOX, connect to an RGB matrix cube and fill it with color.

Start here: **[Getting Started](docs/GETTING_STARTED.md)**

---

## Current SDK status

The public SDK is currently an early **v0.1** release. The first available functionality focuses on:

- Arduino-compatible BLACKBLOX initialization,
- I²C communication,
- RGB Matrix 8×16 cubes,
- multi-matrix displays,
- framebuffer graphics,
- bitmap fonts and the BLACKBLOX font workflow.

Additional cubes, platforms and examples are being added progressively.

---

## Documentation

- [Getting Started](docs/GETTING_STARTED.md)
- [Installation](docs/INSTALLATION.md)
- [Your First Project](docs/FIRST_PROJECT.md)
- [Documentation index](docs/README.md)

Product information, news and future documentation are available at **[get.blackblox.com](https://get.blackblox.com)**.

---

## What can you build?

BLACKBLOX can be used for:

- smart-home and smart-building products,
- information displays and clocks,
- environmental monitoring,
- interactive installations,
- industrial interfaces,
- educational projects,
- IoT devices,
- camera and AI-assisted systems.

The same cubes can move from an experiment to a real installation without throwing away the hardware that helped create it.

---

## Roadmap

Planned areas include:

- additional display cubes,
- environmental and industrial sensors,
- touch interfaces,
- Raspberry Pi support,
- STM32 and RP2350 platform support,
- camera and AI vision modules,
- more complete examples and application projects.

---

## Our mission

We believe the biggest obstacle to innovation is often not technology.

It is time.

Every week between an idea and a working product takes away a little of the excitement that started the project. Ideas lose momentum. Priorities change. Opportunities disappear.

BLACKBLOX exists to shorten that journey.

By combining reusable intelligent hardware with a simple software framework, we help makers, engineers and companies spend less time rebuilding electronics and more time listening to users, testing ideas and improving products.

We do not want you to iterate until the hardware merely works.

We want you to iterate until your customer is happy.

**From idea to working hardware in minutes.**

**Create products. Not prototypes.**

---

## License

See the repository license information before redistribution or commercial use. A dedicated `LICENSE` file will be added as the public licensing terms are finalized.
