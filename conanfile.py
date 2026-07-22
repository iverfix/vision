import os
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain

class ConanConfig(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"  

    def requirements(self):
        self.requires("eigen/5.0.1", force=True)
        self.requires("opencv/4.13.0")
        self.requires("grpc/1.82.0")

    def layout(self):
        self.folders.generators = f"conan/{self.settings.build_type}"

    def configure(self):
        opencv = self.options["opencv"]
        opencv.with_cuda = False
        opencv.with_qt = False
        opencv.with_gtk = False
        opencv.with_vtk = False
        opencv.with_openexr = False
        opencv.with_ffmpeg = True  
        opencv.with_protobuf = False
        opencv.dnn = False

        ffmpeg = self.options["ffmpeg"]

        ffmpeg.with_pulse = False
        ffmpeg.with_vaapi = False
        ffmpeg.with_vdpau = False
        ffmpeg.with_xcb = False
        ffmpeg.with_xlib = False
        ffmpeg.with_vulkan = False

    def generate(self):
        tc = CMakeToolchain(self)
        
        if "pulseaudio" in self.dependencies:
            pulse_path = os.path.join(self.dependencies["pulseaudio"].package_folder, "lib", "pkgconfig")
            tc.variables["PKG_CONFIG_PATH"] = pulse_path
            
        tc.generate()

