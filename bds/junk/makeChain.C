{


TChain chain("samp1");

//TFile *f1=new TFile("tesla_halo_1.root");
  TFile* WorkFile = new TFile("WorkFile.root","RECREATE");
  TDirectory* WorkDir=gDirectory;

chain.Add("laserwire_0.root");
chain.Add("laserwire_1.root");
chain.Add("laserwire_2.root");
chain.Add("laserwire_3.root");
chain.Add("laserwire_4.root");
chain.Add("laserwire_5.root");
chain.Add("laserwire_6.root");
chain.Add("laserwire_7.root");
chain.Add("laserwire_8.root");
chain.Add("laserwire_9.root");


  chain->SetDirectory(WorkDir);

  TCanvas *c1=new TCanvas("c1", "Petra laser-wire",1);
  c1->SetLogy(1);

  int i;
  Float_t z0,weight,x,y,E;
  Int_t part;
  chain->SetBranchAddress("x",&x);
  chain->SetBranchAddress("y",&y);
  chain->SetBranchAddress("z0",&z0);
  chain->SetBranchAddress("weight",&weight);
  chain->SetBranchAddress("part",&part);
  chain->SetBranchAddress("E",&E);


  TH1F *calE=new TH1F("cal_energy"," cal Energy",100.,0.,1.5);

}
