# ALL LENGTHS MUST BE GIVEN IN MILLIMETRES
# ALL ROTATIONS MUST BE GIVEN IN RADIANS

DROP DATABASE IF EXISTS VOLUMETEST;
CREATE DATABASE VOLUMETEST;
USE VOLUMETEST;

CREATE TABLE MYTEST_ELLIPTICALCONE (
    PARENTNAME    VARCHAR(32), #
    POSX          DOUBLE(10,3), #
    POSY          DOUBLE(10,3), #
    POSZ          DOUBLE(10,3), #
    RED           DOUBLE(10,3), #
    GREEN         DOUBLE(10,3), #
    BLUE          DOUBLE(10,3), #
    VISATT        VARCHAR(32),  # I = INVISIBLE, S = SOLID, W = WIREFRAME
    XSEMIAXIS     DOUBLE(10,3), #
    YSEMIAXIS     DOUBLE(10,3), #
    LENGTHZ       DOUBLE(10,3), #
    ZCUT          DOUBLE(10,3), #
    ROTPSI        DOUBLE(10,3), #
    ROTTHETA      DOUBLE(10,3), #
    ROTPHI        DOUBLE(10,3), #
    MATERIAL      VARCHAR(32),  # MATERIAL, CGA LITERAL NAME
    NAME          VARCHAR(32)   # NAME OF SOLID, LOGICAL, AND PHYSICAL VOLUME
);

INSERT INTO MYTEST_ELLIPTICALCONE VALUES ("",0.,0., 1000, 0., 0.,1.0,"S",0.5, 0.5,800, 800, 0.0,0.0,0.0, "vacuum","A_ELLIPTICALCONE");
