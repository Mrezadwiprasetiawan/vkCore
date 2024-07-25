
plugins {
    id("com.android.application")
    
}

android {
    namespace = "rpengine.core.vkcore"
    compileSdk = 33
    
    defaultConfig {
        applicationId = "rpengine.core.vkcore"
        minSdk = 28
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"
        ndkVersion = "26.1.10909125"
        
        vectorDrawables { 
            useSupportLibrary = true
        }
        
        externalNativeBuild{
          cmake{
            abiFilters("arm64-v8a")
          }
        }
    }
    
    externalNativeBuild{
          cmake{
            path(file("src/main/cpp/CMakeLists.txt"))
          }
    }
    
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }

    buildTypes {
        release {
            isMinifyEnabled = true
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }

    buildFeatures {
        viewBinding = true
        prefab = true
        
    }
    
}


