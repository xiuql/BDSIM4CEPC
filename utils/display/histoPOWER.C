histoPOWER(char *gmadFile, char *rootFile)
{
	FILE *fp = gSystem->OpenPipe("export _HISTO=1", "r");
	BDSCanvas *b = new BDSCanvas(gmadFile);
	TFile *f = TFile::Open(rootFile);
	TH1F *histo;
	histo = (TH1F*)f->Get("ElossHisto;1"); 
	histo->GetXaxis()->SetLimits(BDSPad::xmin_axis,BDSPad::xmax_axis);
	histo->Draw();
	b->SetHisto(histo); 
	b->cd();
	return(0);
}
