plugins {
    id("java")
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:5.10.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
    implementation("com.microsoft.sqlserver:mssql-jdbc:12.8.1.jre8")
    implementation("org.jgrapht:jgrapht-core:1.5.1")
}


tasks.test {
    useJUnitPlatform()
}
