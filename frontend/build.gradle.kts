plugins {
    application
    id("com.github.johnrengelman.shadow") version "5.1.0"
}

group = "Saccubus"
version = "3.0"

repositories {
    jcenter()
}

dependencies {
    testCompile("junit", "junit", "4.12")
}

application {
    mainClassName = "samples.HelloWorld"
}

java {
    sourceCompatibility = JavaVersion.VERSION_1_8
    targetCompatibility = JavaVersion.VERSION_1_8
}