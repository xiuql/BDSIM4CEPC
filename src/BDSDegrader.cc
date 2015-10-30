#include "BDSDegrader.hh"

#include "BDSAcceleratorComponent.hh"
#include "BDSColours.hh"
#include "BDSGlobalConstants.hh" 
#include "BDSMaterials.hh"
#include "BDSUtilities.hh"

#include "BDSDebug.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"               
#include "G4SubtractionSolid.hh"
#include "G4ExtrudedSolid.hh"

#include "globals.hh" // geant4 globals / types
#include <vector>

BDSDegrader::BDSDegrader (G4String   name, 
                    G4double   length,
                    G4double   outerDiameterIn,
                    G4int      numberWedgesIn,
                    G4double   wedgeLengthIn,
                    G4double   degraderHeightIn,
                    G4double   degraderOffsetIn,
                    G4String   degraderMaterialIn ):
BDSAcceleratorComponent(name, length, 0, "degrader"),
    outerDiameter(outerDiameterIn),
    numberWedges(numberWedgesIn),
    wedgeLength(wedgeLengthIn),
    degraderHeight(degraderHeightIn),
    degraderOffset(degraderOffsetIn),
    degraderMaterial(degraderMaterialIn)
{;}

BDSDegrader::~BDSDegrader()
{;}

void BDSDegrader::BuildContainerLogicalVolume()
{
  //Input Checks
  if (outerDiameter <= 0)
    {
        G4cerr << __METHOD_NAME__ << "Error: option \"outerDiameter\" is not defined or must be greater than 0" <<  G4endl;
        exit(1);
    }
    
  if (numberWedges < 1)
    {
        G4cerr << __METHOD_NAME__ << "Error: option \"numberWedges\" is not defined or must be greater than 0" <<  G4endl;
        exit(1);
    }
    
  if (wedgeLength <= 0)
    {
        G4cerr << __METHOD_NAME__ << "Error: option \"wedgeLength\" is not defined or must be greater than 0" <<  G4endl;
        exit(1);
    }
    
  if (degraderHeight <= 0)
    {
        G4cerr << __METHOD_NAME__ << "Error: option \"degraderHeight\" is not defined or must be greater than 0" <<  G4endl;
        exit(1);
    }

  if (degraderHeight > (0.5*outerDiameter))
    {
        G4cerr << __METHOD_NAME__ << "Error: option \"degraderHeight\" must be less than 0.5 times \"outerDiameter\"" <<  G4endl;
        exit(1);
    }
    
  if (degraderMaterial == "")
    {
        degraderMaterial = "carbon";
    }
    
    
    
  containerSolid = new G4Box(name + "_container_solid",
                                outerDiameter*0.5,
                                outerDiameter*0.5,
                                chordLength*0.5);
    
  G4Material* emptyMaterial = BDSMaterials::Instance()->GetMaterial(BDSGlobalConstants::Instance()->GetEmptyMaterial());
    
  containerLogicalVolume = new G4LogicalVolume(containerSolid,
                                emptyMaterial,
                                name + "_container_lv");
}


void BDSDegrader::Build()
{
  BDSAcceleratorComponent::Build();
    
//    std::cout << "BDSDegrader offset" << degraderOffset << std::endl;
    
  G4Material* material = BDSMaterials::Instance()->GetMaterial(degraderMaterial);
    
  G4double wedgeBasewidth = chordLength/numberWedges - lengthSafety;
    
  G4double maxzoffset = numberWedges*wedgeBasewidth * 0.5;
    
  std::vector<G4TwoVector> rightWedgeSide; //vertex co-ordinates
  std::vector<G4TwoVector> leftWedgeSide;  //vertex co-ordinates

  // Case for even number of wedges
  if (isEven(numberWedges)){
      for(G4int i=0; i < (numberWedges+1); i++){
          if(isEven(i)){
              if(i==0){                     //First half wedge
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
                  rightWedgeSide.push_back( G4TwoVector(wedgeLength, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i+0.5)*wedgeBasewidth) );
              }
              else if(i==numberWedges){     //Last half Wedge
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i-0.5)*wedgeBasewidth) );
                  rightWedgeSide.push_back( G4TwoVector(wedgeLength, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
              }
              else{                         //RHS full wedge(s)
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i-0.5)*wedgeBasewidth) );
                  rightWedgeSide.push_back( G4TwoVector(wedgeLength, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i+0.5)*wedgeBasewidth) );
              }
          }
          else if(isOdd(i)){                //LHS full wedge(s)
              leftWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i-0.5)*wedgeBasewidth) );
              leftWedgeSide.push_back( G4TwoVector(wedgeLength, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
              leftWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i+0.5)*wedgeBasewidth) );
          }
      }
      //Vertices of base part of RHS component for connecting all RHS wedges
      rightWedgeSide.push_back( G4TwoVector(-0.1*wedgeLength, maxzoffset) );
      rightWedgeSide.push_back( G4TwoVector(-0.1*wedgeLength,-1.0*maxzoffset));

      //Vertices of base part of LHS component for connecting all LHS wedges
      leftWedgeSide.push_back( G4TwoVector(0, maxzoffset));
      leftWedgeSide.push_back( G4TwoVector(-0.1*wedgeLength, maxzoffset) );
      leftWedgeSide.push_back( G4TwoVector(-0.1*wedgeLength, -1.0*maxzoffset) );
      leftWedgeSide.push_back( G4TwoVector(0, -1.0*maxzoffset));
  }
  // Case for odd number of wedges.
  else if (isOdd(numberWedges)){
      for(G4int i=0; i < (numberWedges+1); i++){
          if(isEven(i)){
              if(i==0){     //RHS half wedge
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
                  rightWedgeSide.push_back( G4TwoVector(wedgeLength, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i+0.5)*wedgeBasewidth) );
              }
              else{         //RHS full wedge(s)
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i-0.5)*wedgeBasewidth) );
                  rightWedgeSide.push_back( G4TwoVector(wedgeLength, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
                  rightWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i+0.5)*wedgeBasewidth) );
              }
          }
          else if(isOdd(i)){
              if(i==numberWedges){      //LHS half wedge
                  leftWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i-0.5)*wedgeBasewidth) );
                  leftWedgeSide.push_back( G4TwoVector(wedgeLength, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
                  leftWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
              }
              else{                     //LHS full wedge(s)
                  leftWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i-0.5)*wedgeBasewidth) );
                  leftWedgeSide.push_back( G4TwoVector(wedgeLength, (-1.0*maxzoffset) + (i*wedgeBasewidth)) );
                  leftWedgeSide.push_back( G4TwoVector(0, (-1.0*maxzoffset) + (i+0.5)*wedgeBasewidth) );
              }
          }
      }
       //Vertices of base part of RHS component for connecting all RHS wedges
      rightWedgeSide.push_back( G4TwoVector(0, maxzoffset));
      rightWedgeSide.push_back( G4TwoVector(-0.1*wedgeLength, maxzoffset) );
      rightWedgeSide.push_back( G4TwoVector(-0.1*wedgeLength,-1.0*maxzoffset));
      
      //Vertices of base part of LHS component for connecting all LHS wedges
      leftWedgeSide.push_back( G4TwoVector(-0.1*wedgeLength, maxzoffset) );
      leftWedgeSide.push_back( G4TwoVector(-0.1*wedgeLength, -1.0*maxzoffset) );
      leftWedgeSide.push_back( G4TwoVector(0, -1.0*maxzoffset));
      

  }

  
  // Left wedge Solid and logical Volume
  G4ExtrudedSolid* leftWedge = new G4ExtrudedSolid(name + "_leftwedge_solid",
                                                    leftWedgeSide,
                                                    degraderHeight*0.5,
                                                    G4TwoVector(),1, G4TwoVector(), 1);
    
  RegisterSolid(leftWedge);
    
  G4LogicalVolume* leftWedgeLV = new G4LogicalVolume(leftWedge,               // solid
                                                    material,                 // material
                                                    name + "_leftwedge_lv");  // name
  RegisterLogicalVolume(leftWedgeLV);
  
    
  // Right wedge Solid and logical Volume
  G4ExtrudedSolid* rightWedge = new G4ExtrudedSolid(name + "_rightwedge_solid",
                                                    rightWedgeSide,
                                                    degraderHeight*0.5,
                                                    G4TwoVector(),1, G4TwoVector(), 1);
      
  RegisterSolid(rightWedge);
      
  G4LogicalVolume* rightWedgeLV = new G4LogicalVolume(rightWedge,             // solid
                                                    material,                 // material
                                                    name + "_rightwedge_lv"); // name
  RegisterLogicalVolume(rightWedgeLV);
  
  //Offsets for wedge overlap
  G4double xoffsetLeft = degraderOffset * -1.0;
  G4double xoffsetRight = degraderOffset;
    
  //Rotation  of wedges. Left taken to be +VE x direction, right is -VE x direction.
  G4RotationMatrix* rightRot = new G4RotationMatrix;  
  rightRot->rotateX(CLHEP::pi/2.0);  
  RegisterRotationMatrix(rightRot);

  G4RotationMatrix* leftRot = new G4RotationMatrix;  
  leftRot->rotateX(CLHEP::pi/-2.0);
  leftRot->rotateZ(CLHEP::pi);
  RegisterRotationMatrix(leftRot);

    
  //Wedge color
  G4VisAttributes* degraderVisAttr = new G4VisAttributes(*BDSColours::Instance()->GetColour("degrader"));
  leftWedgeLV->SetVisAttributes(degraderVisAttr);
  rightWedgeLV->SetVisAttributes(degraderVisAttr);

  RegisterVisAttributes(degraderVisAttr);
    
    

  //Translation of individual wedge components
  G4ThreeVector rightwedgepos(xoffsetLeft, 0, 0);
  G4ThreeVector leftwedgepos(xoffsetRight, 0, 0);
  
    
  //Placement of individual wedge components
  G4PVPlacement* leftwedgePV = new G4PVPlacement(leftRot,           // rotation
                                            leftwedgepos,           // position
                                            leftWedgeLV,            // its logical volume
                                            name + "_leftwedge_pv", // its name
                                            containerLogicalVolume, // its mother  volume
                                            false,                  // no boolean operation
                                            0,                      // copy number
                                            checkOverlaps);


    
        
  G4PVPlacement* rightwedgePV = new G4PVPlacement(rightRot,         // rotation
                                            rightwedgepos,          // position
                                            rightWedgeLV,           // its logical volume
                                            name + "_rightwedge_pv",// its name
                                            containerLogicalVolume, // its mother  volume
                                            false,                  // no boolean operation
                                            0,                      // copy number
                                            checkOverlaps);
    

    
  RegisterPhysicalVolume(leftwedgePV);
    
  RegisterPhysicalVolume(rightwedgePV);

}
