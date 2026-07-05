import os
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain

class ConanConfig(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"  

    def requirements(self):
        self.requires("eigen/5.0.1", force=True)
        self.requires("opencv/4.13.0")

    def layout(self):
        self.folders.generators = "build"

    def configure(self):
        self.options["opencv"].with_cuda = False
        self.options["opencv"].with_qt = False
        self.options["opencv"].with_gtk = False
        self.options["opencv"].with_vtk = False
        self.options["opencv"].with_openexr = False
        self.options["opencv"].with_ffmpeg = True  

        self.options["ffmpeg"].with_pulse = False
        self.options["ffmpeg"].with_vaapi = False
        self.options["ffmpeg"].with_vdpau = False
        self.options["ffmpeg"].with_xcb = False
        self.options["ffmpeg"].with_xlib = False
        self.options["ffmpeg"].with_vulkan = False

    def generate(self):
        tc = CMakeToolchain(self)
        
        if "pulseaudio" in self.dependencies:
            pulse_path = os.path.join(self.dependencies["pulseaudio"].package_folder, "lib", "pkgconfig")
            tc.variables["PKG_CONFIG_PATH"] = pulse_path
            
        tc.generate()

