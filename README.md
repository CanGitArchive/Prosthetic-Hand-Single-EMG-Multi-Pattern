### TL;DR: 1-minute demo:

![demo](https://github.com/user-attachments/assets/799b33aa-3dcf-4b50-bae4-261e95a23754)

[https://github.com/user-attachments/assets/ee5b2b8d-1e6a-491c-984f-f104147b91c5](https://youtu.be/wjzd32FGVR0)

My ottobock [1], inspired a single EMG but multi grip pattern myoelectric prosthetic hand.

It uses an algorithm called DTW (Dynamic Time Warping) [2], which normally is a speech recognition algorithm, picking 'yes'/'no' like words out of sentences in simple terms. Which is used to create an 'impulse' control instead of 'constant input' like most popular prosthetics over the market.

I presented a short part of this project in IJANSER presentation [3] before.

A very low budged work.
Work includes a pressure sensor to determine if an object is grabbed and how hard it is grabbed by vibrating a small motor over the user's skin to let them know of the hands grip strength so it can be adjusted to preven slipping. 
Encoder and kinematic equations to determine the angle of the fingers.
Motor driver to control the speed.
Voltage regulators in case there is overvoltage.
WIP battery charge indicator.
Calibration UI installed with buttons.
Manual overwrite with buttons.
Multiple possible connections to EMG and motor units.
Wormgear and other mechanical design for increased friction and precise control over the mechanics with high torque.

Work includes C++ on ESP32, double sided hobby work on a circuit, drawing of the circuit, 3d printing, mathematical algorithm uses over code and understanding of literature.

[1] Ottobock. (n.d.). System Electric Hand Digital Twin. Alındı Haziran 22, 2024, https://ottobock.com/

[2] Berndt, D.J., & Clifford, J. (1994).

[3] Kadılar, M. C., Toptaş, E. & Akgün, G. (2024). An EMG-based Prosthetic Hand Design and Control Through Dynamic Time Warping. International Journal of Advanced Natural Sciences and Engineering Researches, 8(2), 339-349. 


Below are some of the images from the project and a working video demonstration I recorded.

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



