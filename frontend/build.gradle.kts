import com.github.jengelman.gradle.plugins.shadow.tasks.ShadowJar

plugins {
    application
    java
    idea
    kotlin("jvm") version "1.3.41"
    id("com.github.johnrengelman.shadow") version "5.1.0"
}

group = "Saccubus"
version = "3.0"

repositories {
    jcenter()
}

dependencies {
    implementation(kotlin("stdlib"))
    testCompile("junit", "junit", "4.12")
    compile("com.google.code.gson", "gson", "2.8.6")
}

tasks.withType<ShadowJar>() {
    manifest {
        attributes["Main-Class"] = "saccubus.Saccubus"
    }
}

application {
    mainClassName = "saccubus.Saccubus"
}

java {
    sourceCompatibility = JavaVersion.VERSION_12
    targetCompatibility = JavaVersion.VERSION_12
}