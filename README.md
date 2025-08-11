### TL;DR: 1-minute demo:

![demo](https://github.com/user-attachments/assets/799b33aa-3dcf-4b50-bae4-261e95a23754)

> Click to watch full video on youtube:

[![Watch the demo](https://img.youtube.com/vi/wjzd32FGVR0/hqdefault.jpg)](https://youtu.be/wjzd32FGVR0)

> Control a multi-grip prosthetic hand using **one** EMG sensor by matching brief muscle “impulses” with **DTW** on an **ESP32**. Four grips via binary impulse patterns (**00, 01, 10, 11**). ~**92%** accuracy in tests; **~414–644 ms** impulse-to-motion latency.

**Tech stack:** ESP32 • C++/PlatformIO • DTW template matching • Rotary encoder • 3D-printed PLA

## What this is (Problem → Idea → Outcome)

* **Problem:** Multi-sensor myoelectric hands are accurate but **complex/expensive**; accessible control with fewer sensors is desirable.
* **Idea:** Use **one EMG channel** and **Dynamic Time Warping (DTW)** to match brief, user-taught impulse shapes to template patterns.
* **Outcome:** A working prototype with **four reliable grips** from binary impulse combos, measured **92% accuracy** and **\~0.4–0.6 s** latency on **ESP32** firmware.

## Highlights

* **Single-sensor control:** one sEMG channel → multi-pattern control (binary combos).
* **On-device DTW:** template matching runs on **ESP32** (C++/PlatformIO).
* **Mechanism:** DC motor **+ worm gear** for torque; **rotary encoder** for position/limits.
* **DIY-ready:** 3D-printed PLA mechanism; simple **UI-based calibration**; data logged at **\~20 ms** intervals.
* **Safety:** encoder-based travel limits; impulse-based discrete commands.

## System Overview

```
[ sEMG electrode ] → [ filter/amplify ] → [ ESP32: DTW matcher ]
→ [ pattern decoded (00/01/10/11) ] → [ grip controller ]
→ [ motor driver ] → [ DC motor + worm gear + fingers (encoder-limited) ]
```

* **Calibration:** record two impulse templates (Pattern 0 / Pattern 1).
* **Control:** live sEMG is DTW-matched against templates; two sequential detections form a **binary pair** (e.g., `0` then `1` → **01**) that selects the grip.

## Specs (Prototype)

| Category                | Value                                 |
| ----------------------- | ------------------------------------- |
| Channels                | 1× surface EMG (3-lead)               |
| Sampling/logging        | \~**20 ms** intervals                 |
| Patterns                | **4** (00, 01, 10, 11)                |
| Accuracy (4-class)      | **\~92%** (46/50 correct)             |
| Latency (impulse→motor) | **\~414–644 ms**                      |
| MCU / Firmware          | **ESP32** / C++ (PlatformIO)          |
| Drive                   | DC motor + **worm gear**              |
| Sensing                 | **Rotary encoder** (limits & control) |
| Prints                  | **PLA** (STLs included)               |


## Quickstart
1. **Assemble** the mechanism (print parts, install worm gear, mount encoder and motor).
2. **Wire** EMG module → ESP32; encoder → ESP32; driver → motor.
3. **Flash**: `pio run -t upload` (PlatformIO).
4. **Calibrate**: record **Pattern 0** and **Pattern 1** templates.
5. **Drive**: perform two impulses to select grip (**00/01/10/11**). Motion is **encoder-limited**.

## Bill of Materials (major items)

* 1× **ESP32 DevKit** (e.g., ESP32-WROOM)
* 1× **sEMG module** + 3 electrodes (live/neutral/ground)
* 1× **DC gear motor** (torque suited for finger actuation)
* 1× **Worm gear set** + slider/finger linkages (3D-printed)
* 1× **Rotary encoder** (motor or output shaft)
* 1× **Motor driver** (ESP32-compatible)
* **Power** (battery or bench) • **Wires** • **Fasteners** • **SD card** (optional logging)

See **[BOM.md](./BOM.md)** for prices (TRY, 2024) and USD/CAD conversions.

## Results

* **Confusion matrix (4-class)**: 46 correct / 4 wrong → **\~92%**.
* **Latency**: impulse→motor start **\~414–644 ms** (DTW match threshold crossing to actuation).
* **Notes**: latency trades off with robustness (lower threshold = faster but noisier). Include your recorded thresholds and any failure modes.

## Repo Structure

```
/firmware/           # ESP32 (PlatformIO) source
/hardware/           # schematic.pdf, wiring.pdf
/cad/                # STEP files
/stl/                # printable parts
/data/               # sample EMG logs (CSV)
/docs/               # figures (system diagram, confusion matrix, latency)
/scripts/            # parsing/plotting DTW logs (Python)
```

## Roadmap

* Add **haptic feedback** band (vibration/piezo) for grip confirmation.
* Optional **ROS 2** bridge node (USB serial → ROS topic) for sim/integration.
* Tune DTW thresholds per user **fatigue**; add auto-recalibration over time.

## Safety & License

This is a **research prototype**, **not** a medical device. Use at your own risk.
License: **MIT** (or your preferred license).

## Article(s)

### Published:
KADILAR, M. C., TOPTAŞ, E., & AKGÜN, G. (2024). An EMG-based Prosthetic Hand Design and Control Through Dynamic Time Warping. International Journal of Advanced Natural Sciences and Engineering Researches, 8(2), 339–349. Retrieved from https://as-proceeding.com/index.php/ijanser/article/view/1728

### In review:
**Kadılar, M.C.; Toptaş, E.; Akgün, G.** “Impulsive pattern recognition of a myoelectric hand via Dynamic Time Warping,” *IEEE Trans. Med. Robotics and Bionics*, 2025.
https://doi.org/10.48550/arXiv.2504.15256

## Acknowledgments

Thanks to Marmara University advisors and labs.

## Below are figures and tables:

### Confusion matrix of intended patterns:
<img width="336" height="115" alt="image" src="https://github.com/user-attachments/assets/6e23a044-416c-4d61-ac06-a3a5e2bad920" />

### Delay due to the nature of DTW algorithm:
<img width="336" height="253" alt="image" src="https://github.com/user-attachments/assets/67f9cb18-25fe-4c41-9a34-a5b1bed7d31d" />

### EMG probe connections:

![EMG Probes](https://github.com/user-attachments/assets/c286c6e3-3aae-4f18-991e-e6e62725d567)

### Circuit topdown view:

![E Circuit](https://github.com/user-attachments/assets/dcf46c61-ebfa-4250-a517-7626e3944b9f)

### PCB Drawing:

![pcbnew_rA4Q7lQbw3](https://github.com/user-attachments/assets/0701f87a-ca53-46b9-9a88-1d37206926b3)

### 3D mechanical design:

![3DView](https://github.com/user-attachments/assets/ef785796-5f56-4458-9748-d2fed3997954)

### Calibration process:

![OLED](https://github.com/user-attachments/assets/c69b61e3-642b-458f-b2a8-5e7c67c7c2f6)

### Full setup view:

![Layer 10](https://github.com/user-attachments/assets/25244ae5-5a1d-4c5f-933f-386d501a663f)



