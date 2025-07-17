# miniRT

## Mandatory Part

### Overview  
**miniRT** is your first C ray‑tracer using MiniLibX. It reads a simple scene description (`*.rt`) and renders a 3D image with basic ray‑tracing (ambient + diffuse lighting, hard shadows).

### Usage

```bash
make                # builds the program (all, clean, fclean, re, bonus)
./miniRT scene.rt   # render the scene described in "scene.rt"
```

### Requirements

- **Program name:** `miniRT`  
- **Turn in files:** All your `.c` / `.h` sources, plus your `Makefile`  
- **Makefile rules:** `all`, `clean`, `fclean`, `re`, `bonus`  
- **Arguments:** one `.rt` file describing the scene  
- **Allowed external functions:**  
  - Standard C: `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`  
  - Math library (`-lm`): all functions from `<math.h>`  
  - MiniLibX API  
- **Libft:** you may use your libft (copy its sources into `libft/` and have your Makefile build it)  
- **Project enforced to the Norm**: any Norm violation in mandatory (or bonus) files yields 0.

---

## Scene Description File (`*.rt`)

- Elements may appear in any order, separated by blank lines or spaces.
- Elements identified by uppercase letters (`A`, `C`, `L`) or two‑letter codes (`sp`, `pl`, `cy`).
- Capital‑letter elements may only be declared **once**.

### Element Formats

1. **Ambient lighting**  
   ```
   A [ratio] [R,G,B]
   ```  
   - `ratio` ∈ [0.0, 1.0]  
   - color channels 0–255  

2. **Camera**  
   ```
   C [x,y,z] [nx,ny,nz] [FOV]
   ```  
   - position `[x,y,z]` (floats)  
   - normalized orientation vector `[-1..1]` each  
   - horizontal field of view `FOV`° ∈ [0, 180]  

3. **Light**  
   ```
   L [x,y,z] [ratio] [R,G,B]
   ```  
   - position `[x,y,z]`  
   - brightness `ratio` ∈ [0.0, 1.0]  
   - color channels 0–255 (ignored in mandatory part)

4. **Sphere**  
   ```
   sp [x,y,z] [diameter] [R,G,B]
   ```  
   - center `[x,y,z]`  
   - `diameter` (float)  
   - color 0–255  

5. **Plane**  
   ```
   pl [x,y,z] [nx,ny,nz] [R,G,B]
   ```  
   - a point on the plane `[x,y,z]`  
   - normalized normal vector `[-1..1]` each  
   - color 0–255  

6. **Cylinder**  
   ```
   cy [x,y,z] [nx,ny,nz] [diameter] [height] [R,G,B]
   ```  
   - center `[x,y,z]`  
   - normalized axis vector `[-1..1]` each  
   - `diameter`, `height` (floats)  
   - color 0–255  

### Constraints & Features

- **Geometry:** sphere, plane, cylinder only  
- **Intersections:** handle all intersection cases, including “inside” hits  
- **Transformations:** translation & rotation for objects, lights, camera (except spheres & lights can’t rotate)  
- **Lighting:**  
  - ambient term  
  - diffuse term  
  - hard shadows  
- **Display:**  
  - render into a MiniLibX window  
  - ESC or window close (“red cross”) must cleanly exit  
  - window resizing / focus changes must remain fluid  

### Error Handling

If the `.rt` file is malformed or any constraint is violated, the program must:

1. Print  
   ```
   Error
   <your explicit error message>
   ```  
2. Exit cleanly (non‑zero status).

---

## Minimal Example (`example.rt`)

```rt
A 0.2 255,255,255

C -50,0,20   0,0,1   70
L -40,0,30   0.7     255,255,255

pl  0,0,0     0,1,0    255,0,225
sp  0,0,20    20       255,0,0
cy 50,0,20.6  0,0,1   14.2 21.42 10,0,255
```