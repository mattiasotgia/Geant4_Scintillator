//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  // World

  G4double sizeXY = 20*cm, sizeZ = 30*cm;
  G4double world_sizeXY = 1.2*sizeXY;
  G4double world_sizeZ  = 1.2*sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld = new G4Box("World",                           // its name
    world_sizeXY, world_sizeXY, world_sizeZ);  // its size
  
  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
    world_mat,                                       // its material
    "World");                                        // its name
  
  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                           // at (0,0,0)
    logicWorld,                                // its logical volume
    "World",                                   // its name
    nullptr,                                   // its mother  volume
    false,                                     // no boolean operation
    0,                                         // copy number
    checkOverlaps);                            // overlaps checking
  
  //
  // Counter

  G4Material* shape_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4double shape_sizeXY = 0.1 * world_sizeXY;
  G4double shape_sizeZ  = 0.1 * world_sizeZ;
  
  G4ThreeVector pos = G4ThreeVector(0, 0, shape_sizeZ/2);

  // Box
  auto solidShape = new G4Box("Counter",       // its name
    shape_sizeXY, shape_sizeXY, shape_sizeZ);  // its size

  auto logicShape = new G4LogicalVolume(solidShape,  // its solid
    shape_mat,                                       // its material
    "Counter");                                      // its name

  auto physShape  = new G4PVPlacement(nullptr,  // no rotation
    pos,                                        // at position
    logicShape,                                 // its logical volume
    "Counter",                                  // its name
    logicWorld,                                 // its mother  volume
    false,                                      // no boolean operation
    0,                                          // copy number
    checkOverlaps);                             // overlaps checking

  // Set Shape as scoring volume
  fScoringVolume = logicShape;

  //always return the physical World
  return physWorld;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

