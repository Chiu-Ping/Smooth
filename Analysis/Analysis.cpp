#include "Channel.hpp"
#include "Event.hpp"
#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH1F.h"
#include <vector>
#include "TTreeReader.h"
#include "TSpectrum.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TAxis.h"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{ 	
	TString Num_data;
	
	std::cout << argc <<" " << argv[0] << " " << argv[1] << std::endl; 
	if( argc<0 || argc>3)
    {
		std::cout << "It NEED only one string pararemeter for the data NAME!" << std::endl; 
		exit(-5);  
	}
  	else 
    	Num_data = std::string(argv[1]);

	//TFile fileIn("/home/shenqiuping/RPC_Anal/data/New_Data/Run_"+Num_data+".root");
	TFile fileIn("/home/shenqiuping/RPC_Anal/data/Run_"+Num_data+".root");
	if (fileIn.IsZombie()) 
	{
  		std::cout << "Error opening file: Run_" << Num_data << ".root file doesn't exsist!" << std::endl;
		exit(-1);
	}

//	std::ofstream out("./Procees_content.txt");
//	std::ofstream log("./Run_"+Num_data+".txt");
//	std::ofstream ratiof("./Ratio_4.txt");
//	std::ofstream ratiow("./Ratio_5.txt");
	std::ofstream toto("./Totoal_Info.txt");
	
/*****************************Code for inputing the signal samples****************************/
	Int_t Signal_info[2][9999]={0},Nsig=0;
	std::ifstream infile;
	infile.open("/home/shenqiuping/RPC_Anal/Smooth/Run/Signal.txt");
	if (!infile.is_open()) exit (EXIT_FAILURE);
	
	for(Int_t i=0;!infile.eof();i++)
	{
		infile >> Signal_info[0][i] >> Signal_info[1][i];
	//	std::cout << Signal_info[0][i] << "\t" << Signal_info[1][i] << std::endl;
		Nsig++;
	}
	infile.close();

/****************************Code for processing data******************************************/
/***********************define many variables*******************************/
   	TTree *t1 = (TTree*)fileIn.Get("Tree");
   	Event* event{nullptr};
   	t1->SetBranchAddress("Events",&event);
    TCanvas *c_SN_sjtu = new TCanvas("c_SN_sjtu","RPC Sig & Bkg",800,600);
    TCanvas *c_SN_ustc = new TCanvas("c_SN_ustc","RPC Sig & Bkg",800,600);
   
   	Double_t Eff[32]={0};
   	Int_t Nsig_SJTUf=0,Nsig_USTCf=0,Nsig_SJTUw=0,Nsig_USTCw=0;
    Int_t Nsig_SJTU_Tot=0,Nsig_USTC_Tot=0,Nbkg_Tot_u=0,Nbkg_Tot_s=0,
			Nbkg_sig_uf=0,Nbkg_sig_sf=0,
			Nbkg_sig_uw=0,Nbkg_sig_sw=0,
			Ntot_Evn_u=0, Ntot_Evn_s=0; 
   
   	TH1F *Hist_SigmaCh[32]; 
    TH1F *Hist_SN_Ratio_ChP[32];  
    TH1F *Hist_SN_Ratio_ChN[32];  
    
	TH1F *Hist_SN_Ratio_sjtu = new TH1F("Hist_SN_Ratio_sjtu","",30,-0.01,15); 
    TH1F *Hist_BG_Ratio_sjtu = new TH1F("Hist_BG_Ratio_sjtu","",30,-0.01,15);
    TH1F *Hist_SN_Ratio_ustc = new TH1F("Hist_SN_Ratio_ustc","",30,-0.01,15); 
    TH1F *Hist_BG_Ratio_ustc = new TH1F("Hist_BG_Ratio_ustc","",30,-0.01,15);

	Double_t Hist_bin[999999];
	Int_t 	Nsig_SJTU=0,Nsig_USTC=0,
			Nbkg_SJTU=0,Nbkg_USTC=0,
			Nsig_SJTUfch=0,Nsig_USTCfch=0,
			Nsig_SJTUech=0,Nsig_USTCech=0,
			Nbkg_SJTUfch=0,Nbkg_USTCfch=0,
			Nbkg_SJTUech=0,Nbkg_USTCech=0,
   			Nsig_Trigger_s[32]={0}, Nsig_Trigger_u[32]={0};	
	//read all entries and fill the histogram

   Long64_t nentries = t1->GetEntries(); 
   std::cout<< "Total events:"<< nentries << std::endl;
   
   for (Long64_t i=0;i<nentries;i++) 
   {	
   	 //if(i<=1000)
	 //{	 		 
	 Bool_t NegSig_Truth[32];

	t1->GetEntry(i);
//	log <<event->EventNumber<<
// 		"**********************************************************" << std::endl; 
	for(unsigned int channel=0;channel!=18;++channel)
     {
        double min{999999};
        double max{-99999};
		double Sm_Mean[1024],Sum=0,Max_mean=0,Min_mean=10,Sigma_y=0,Sum_Sigma=0;
        double NbrTicks=event->Channels[channel].Data.size();
        double MaxTime=event->Channels[channel].Time[NbrTicks-1];
  
        TCanvas can;
        TH1F *test = new TH1F("Test","Test",NbrTicks,0,NbrTicks);
        TH1F *smooth = new TH1F("Smooth","Smooth",NbrTicks,0,NbrTicks);  //adding the raw smooth      

        for(unsigned int j=0;j!=event->Channels[channel].Data.size();++j)
        {
            if(event->Channels[channel].Data[j]*1.0/4096<min)min=event->Channels[channel].Data[j]*1.0/4096;
            else if (event->Channels[channel].Data[j]*1.0/4096>max) max=event->Channels[channel].Data[j]*1.0/4096;
            test->Fill(j,event->Channels[channel].Data[j]*1.0/4096);
            test->GetYaxis()->SetRangeUser(min-((max-min)/20.0),max+((max-min)/20.0));
            test->SetLabelColor(kRed); 
/********************************Smooth the data with a window including five points******************************************************/            
            if( j<2 || j>1021 ) 
				Sm_Mean[j]=event->Channels[channel].Data[j]*1.0/4096;
			else 
				Sm_Mean[j]=0.2*(event->Channels[channel].Data[j+2]*1.0/4096+event->Channels[channel].Data[j+1]*1.0/4096+event->Channels[channel].Data[j]*1.0/4096+event->Channels[channel].Data[j-1]*1.0/4096+event->Channels[channel].Data[j-2]*1.0/4096);           
   			
	   		smooth->Fill(j,Sm_Mean[j]); 
     		smooth->GetYaxis()->SetRangeUser(min-((max-min)/20.0),max+((max-min)/20.0));
            smooth->SetLabelColor(kGreen); 
	  		Sum=Sum+Sm_Mean[j];
			if(j>70 && j<250)
			{
				if(Sm_Mean[j]>Max_mean) Max_mean=Sm_Mean[j];
				if(Sm_Mean[j]<Min_mean) Min_mean=Sm_Mean[j];	
			}			
		}
			
/****************************Code for processing data & making a plot on Sig & Bkg @ SJTU Data***********************************************/		
	//	if(channel==10 || channel==13 ||channel==14 || channel==15 || channel==11 ||channel==12 || channel==16 || channel==9)
		if(channel==10 || channel==13 ||channel==14 || channel==15)
		{
			Ntot_Evn_s++;
			NegSig_Truth[channel]=false; 
			for(int k=0;k<NbrTicks;++k) 
			{
				Sum_Sigma=(Sm_Mean[k]-Sum/NbrTicks)*(Sm_Mean[k]-Sum/NbrTicks)+Sum_Sigma;	
			} 
	  		Sigma_y=sqrt(Sum_Sigma/NbrTicks); //After smoothing, the RMS along Y-direction
			
			/**********************************For Training(known the ratio of signal and backgorund)**************/
			/*Bool_t Sig_true = false;
			for(Int_t a=0; a<Nsig; a++)
			{
				if(Signal_info[0][a]==i && Signal_info[1][a]==channel)	{Sig_true = true; NegSig_Truth[channel]=true;}	
			}
			if(Sig_true == true) 
			{
				Hist_SN_Ratio_sjtu->Fill((Sum/NbrTicks-Min_mean)/Sigma_y);
				Nsig_SJTU_Tot++; 		
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>4.000) Nsig_SJTUf++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>5.000) Nsig_SJTUw++;	
			}
			else 
			{
				Hist_BG_Ratio_sjtu->Fill((Sum/NbrTicks-Min_mean)/Sigma_y);
				Nbkg_Tot_s++;
			//	if(((Sum/NbrTicks-Min_mean)/Sigma_y)> 9 && ((Sum/NbrTicks-Min_mean)/Sigma_y)<14 ) std::cout << i << "\t" << channel << std::endl;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>4.00) Nbkg_sig_sf++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>5.000) Nbkg_sig_sw++;
			}*/
			
			/**********************************For applying to all of events**************************************/
			if(((Sum/NbrTicks-Min_mean)/Sigma_y)>4.000)  NegSig_Truth[channel]=true; 
			//else NegSig_Truth[channel]=false;
		}
	//	std::cout << Nsig_SJTU_Tot << " \t" << "Successful!" <<std::endl;
/****************************Code for processing data & making a plot on Sig & Bkg @ USTC Data***********************************************/		
		if(channel==0 || channel==1 ||channel==2 || channel==3 || channel==4 || channel==5 || channel==6 || channel==7)	
		{
			Ntot_Evn_u++;
			NegSig_Truth[channel]=false; 
			for(int k=0;k<NbrTicks;++k) 
			{
				Sum_Sigma=(Sm_Mean[k]-Sum/NbrTicks)*(Sm_Mean[k]-Sum/NbrTicks)+Sum_Sigma;
			} 
			Sigma_y=sqrt(Sum_Sigma/NbrTicks);  //After smoothing, the RMS along Y-direction
			
			/**********************************For Training(known the ratio of signal and backgorund)**************/
			/*Bool_t Sig_true = false;
			for(Int_t a=0; a<Nsig; a++)
			{
				if(Signal_info[0][a]==i && Signal_info[1][a]==channel)	{Sig_true = true; NegSig_Truth[channel]= true;} 	
			}
			if(Sig_true == true) 
			{
				Hist_SN_Ratio_ustc->Fill((Sum/NbrTicks-Min_mean)/Sigma_y); 
				Nsig_USTC_Tot++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>3.525) Nsig_USTCf++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>5.000) Nsig_USTCw++;
			}
			else 
			{
				Hist_BG_Ratio_ustc->Fill((Sum/NbrTicks-Min_mean)/Sigma_y);
				Nbkg_Tot_u++;
			//	if(((Sum/NbrTicks-Min_mean)/Sigma_y)> 9 && ((Sum/NbrTicks-Min_mean)/Sigma_y)<14 ) std::cout << i << "\t" << channel << std::endl;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>3.525) Nbkg_sig_uf++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>5.000) Nbkg_sig_uw++;	
			}*/
			
			/**********************************For applying to all of events**************************************/
			if(((Sum/NbrTicks-Min_mean)/Sigma_y)>3.525) NegSig_Truth[channel]= true;
			//else NegSig_Truth[channel]=false;			
		}
		//std::cout << Nsig_USTC_Tot << " \t" << "Successful!" <<std::endl;

		
		/****************************************Code for trigger process counters**********************************/
			if((channel==8 || channel == 17) )  //This is a trigger cut&& ((Sum/NbrTicks-Min_mean)/Sigma_y)>2 
	 	{
 		//	log << "there is a negative trigger signal!" << std::endl;
   			
	   		if(channel==8) Nsig_Trigger_u[8]++; 
	   		else Nsig_Trigger_s[17]++;	
   		//	out << event->EventNumber << " " << Sigma_y << "\t" << "Negative!" <<"\n" ;
 		} 

/****************************Code for finding a peak with signal/background***********************************************/
		can.Divide(1,2);
        can.cd(1);
 		test->SetMarkerStyle(kFullSquare);
		test->SetTitle(("Event"+std::to_string(i)+"_Channel"+std::to_string(channel)).c_str());
 		test->Draw("HIST");
		
		can.cd(2);
		smooth->SetMarkerStyle(kFullSquare);
		smooth->SetTitle(("Smooth"+std::to_string(i)+"_Channel"+std::to_string(channel)).c_str());
 		smooth->Draw("HIST");

        //can.SaveAs(("Event&smooth"+std::to_string(i)+"_Channel"+std::to_string(channel)+".png").c_str());
        test->Clear();
		smooth->Clear(); 
		} //channel loop
//	log << "**********************************************************" << std::endl;
/***************************************Output the efficiency information  &  4-chs 8-chs efficiency comparision for samples with known ratio of signal-background****************************************/	
/*		if(NegSig_Truth[10] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15] || NegSig_Truth[12] || NegSig_Truth[11] || NegSig_Truth[9] || NegSig_Truth[16])
			Nsig_SJTUech++;
		if(NegSig_Truth[1] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6] || NegSig_Truth[0] || NegSig_Truth[2] || NegSig_Truth[3] || NegSig_Truth[7])
			Nsig_USTCech++;
		
		if(NegSig_Truth[10] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15])
			Nsig_SJTUfch++;
		if(NegSig_Truth[1] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6])
			Nsig_USTCfch++;	
		
		if(NegSig_Truth[10] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15])
			Nsig_SJTU++;
		if(NegSig_Truth[0] || NegSig_Truth[1] || NegSig_Truth[2] || NegSig_Truth[3] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6] || NegSig_Truth[7])
			Nsig_USTC++;
*/		
//		log << "/***********************************/" << std::endl;	
/*		log << Nsig_Trigger_u[8] << "\t" << Nsig_Trigger_s[17] << std::endl;
	  	log << "USTC Efficiency_8chs: " << 1.0*Nsig_USTCech/Nsig_Trigger_u[8] << ";\t\n"
				  << "SJTU Efficiency_8chs: " << 1.0*Nsig_SJTUech/Nsig_Trigger_s[17] << ";\t" << ((1.0*Nsig_SJTUf/Ntot_Evn_s)/(1.0*Nsig_USTCf/Ntot_Evn_u))*(1.0*Nsig_USTCech/Nsig_Trigger_u[8]) << std::endl;
	  	log << "USTC Efficiency_4chs: " << 1.0*Nsig_USTC/Nsig_Trigger_u[8] << ";\t\n"
				  << "SJTU Efficiency_4chs: " << 1.0*Nsig_SJTU/Nsig_Trigger_s[17] << ";\t" << ((1.0*Nsig_SJTUf/Ntot_Evn_s)/(1.0*Nsig_USTCf/Ntot_Evn_u))*(1.0*Nsig_USTC/Nsig_Trigger_u[8]) << std::endl;
	  	log << "USTC Efficiency_s4_u8chs: " << 1.0*Nsig_USTCfch/Nsig_Trigger_u[8] << ";\t\n"
				  << "SJTU Efficiency_s4_u8chs: " << 1.0*Nsig_SJTUfch/Nsig_Trigger_s[17] << ";\t" << ((1.0*Nsig_SJTUf/Ntot_Evn_s)/(1.0*Nsig_USTCf/Ntot_Evn_u))*(1.0*Nsig_USTCfch/Nsig_Trigger_u[8]) << std::endl;
*/		
/***********************************Apply to all of events. Real signal output through Ns_real*Signal_Eff & Fake rate*Nb_real = Ns_Selected*******************************************/ 		
		/*******************************Signal manipulation***************************************************/
	/*	if(NegSig_Truth[10] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15] || NegSig_Truth[12] || NegSig_Truth[11] || NegSig_Truth[9] || NegSig_Truth[16])
			Nsig_SJTUech++;
		if(NegSig_Truth[1] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6] || NegSig_Truth[0] || NegSig_Truth[2] || NegSig_Truth[3] || NegSig_Truth[7])
			Nsig_USTCech++;	
	
		if(NegSig_Truth[10] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15])
			Nsig_SJTUfch++;
		if(NegSig_Truth[1] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6])
			Nsig_USTCfch++;	
		*/
		if(NegSig_Truth[10] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15])
			Nsig_SJTU++;
		if(NegSig_Truth[0] || NegSig_Truth[1] || NegSig_Truth[2] || NegSig_Truth[3] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6] || NegSig_Truth[7])
			Nsig_USTC++;
		toto << "/********************************************************/" << std::endl;
		toto << "Ntotoal_events: " << nentries << std::endl;
		toto << "\t\t\t" << "SJTU" << "\t" << "USTC" << std::endl;	
		toto << "Nsig_selected_8chs:\t" << Nsig_SJTUech << "\t" << Nsig_USTCech <<std::endl;
		toto << "Nsig_selected_4chs:\t" << Nsig_SJTUfch << "\t" << Nsig_USTCfch <<std::endl;
		toto << "Nsig_selected_s4_u8chs:\t" << Nsig_SJTU << "\t" << Nsig_USTC <<std::endl;
		
		if(i==1001)
		{
			std::cout << "\t\t\t" << "SJTU" << "\t" << "USTC" << std::endl;	
			std::cout << "Nsig_selected_8chs:\t" << Nsig_SJTUech << "\t" << Nsig_USTCech <<std::endl;
			std::cout << "Nsig_selected_4chs:\t" << Nsig_SJTUfch << "\t" << Nsig_USTCfch <<std::endl;
			std::cout << "Nsig_selected_s4_u8chs:\t" << Nsig_SJTU << "\t" << Nsig_USTC <<std::endl;
		}
	
		/*******************************Background manipulation***************************************************/
	/*	if(!(NegSig_Truth[10] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15] || NegSig_Truth[12] || NegSig_Truth[11] || NegSig_Truth[9] || NegSig_Truth[16]))
			Nbkg_SJTUech++;
		if(!(NegSig_Truth[1] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6] || NegSig_Truth[0] || NegSig_Truth[2] || NegSig_Truth[3] || NegSig_Truth[7]))
			Nbkg_USTCech++;	
	
		if(!(NegSig_Truth[10] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15]))
			Nbkg_SJTUfch++;
		if(!(NegSig_Truth[1] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6]))
			Nbkg_USTCfch++;	
*/
		if(!(NegSig_Truth[10] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15]))
			Nbkg_SJTU++;
		if(!(NegSig_Truth[0] || NegSig_Truth[1] || NegSig_Truth[2] || NegSig_Truth[3] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6] || NegSig_Truth[7]))
			Nbkg_USTC++;
		toto << "/********************************************************/" << std::endl;
		toto << "Ntotoal_events: " << nentries << std::endl;
		toto << "\t\t\t" << "SJTU" << "\t" << "USTC" << std::endl;	
		toto << "Nbkg_selected_8chs:\t" << Nbkg_SJTUech << "\t" << Nbkg_USTCech <<std::endl;
		toto << "Nbkg_selected_4chs:\t" << Nbkg_SJTUfch << "\t" << Nbkg_USTCfch <<std::endl;
		toto << "Nbkg_selected_s4_u8chs:\t" << Nbkg_SJTU << "\t" << Nbkg_USTC <<std::endl;
		
		if(i==1000)
		{
			std::cout << "\t\t\t" << "SJTU" << "\t" << "USTC" << std::endl;	
			std::cout << "Nbkg_selected_8chs:\t" << Nbkg_SJTUech << "\t" << Nbkg_USTCech <<std::endl;
			std::cout << "Nbkg_selected_4chs:\t" << Nbkg_SJTUfch << "\t" << Nbkg_USTCfch <<std::endl;
			std::cout << "Nbkg_selected_s4_u8chs:\t" << Nbkg_SJTU << "\t" << Nbkg_USTC <<std::endl;
		}
	
	//}  //if end 
	if((i%1000)==0) std::cout<< "Processed events:"<< i << ", \t" << (Float_t)i/nentries << std::endl;
     	event->clear();
   }  //Event end

/*******************************code for the process of output files   LATEX format*****************************/  
   /****************************Output information for training*************************************/
	//	ratiof << "\t" << "(Mean-MinValue)/RMS=Ratio>4" << "\t" << std::endl; 
/*		ratiof << "\\hline" << std::endl;
		ratiof << "$N_{tot}$" << "\t" << "&" << "&$N_{sig}$" << "\t" << "&" << "$N_{sig}(Eff)$" << "\t" << "&" << "$Nbg_{tot}$" << "\t" << "&" << "$Nbk(fake\\ rate)$\\" << "\\" << std::endl;
		ratiof << "\\hline" << std::endl;
		ratiof << "$SJTU$($Ratio=(Mean-min)/RMS>4$)" << "\t" << "&" << Ntot_Evn_s << "\t" << "&" << Nsig_SJTUf << "\t" << "&" << Nsig_SJTU_Tot << "(" << 100.00*Nsig_SJTUf/Nsig_SJTU_Tot << "\\" << "\%)" << "\t" << "&" << Nbkg_Tot_s << "\t" << "&" << 100.00*Nbkg_sig_sf/Nbkg_Tot_s << "\\" << "\%\\" << "\\" << std::endl;   //SJTU-Ratio-4
		ratiof << "\\hline" << std::endl;
		ratiof << "$USTC$($Ratio=(Mean-min)/RMS>3.525$)" << "\t" << "&" << Ntot_Evn_u << "\t" << "&" << Nsig_USTCf << "\t" << "&" << Nsig_USTC_Tot << "(" << 100.00*Nsig_USTCf/Nsig_USTC_Tot << "\\" << "\%)" << "\t" << "&" << Nbkg_Tot_u << "\t" << "&" << 100.00*Nbkg_sig_uf/Nbkg_Tot_u << "\\" << "\%\\" << "\\" << std::endl;   //USTC-Ratio-4
		ratiof << "\\hline" << std::endl;
		
	//	ratiow << "\t" << "(Mean-MinValue)/RMS=Ratio>5" << "\t" << std::endl; 
		ratiow << "\\hline" << std::endl;
		ratiow <<  "$N_{tot}$" << "\t" << "&" << "&$N_{sig}$" << "\t" << "&" << "$N_{sig}(Eff)$" << "\t" << "&" << "$Nbg_{tot}$" << "\t" << "&" << "$Nbk(fake\\ rate)$\\" << "\\" <<std::endl;
		ratiow << "\\hline" << std::endl;
		ratiow << "$SJTU$($Ratio=(Mean-min)/RMS>5$)" << "\t" << "&" << Ntot_Evn_s << "\t" << "&" << Nsig_SJTUw << "\t" << "&" << Nsig_SJTU_Tot << "(" << 100.00*Nsig_SJTUw/Nsig_SJTU_Tot << "\\" << "\%)" << "\t" << "&" << Nbkg_Tot_s << "\t" << "&" << 100.00*Nbkg_sig_sw/Nbkg_Tot_s << "\\" << "\%\\" << "\\" << std::endl;   //SJTU-Ratio-5
   	    ratiow << "\\hline" << std::endl;
  		ratiow << "$USTC$($Ratio=(Mean-min)/RMS>5$)" << "\t" << "&" << Ntot_Evn_u << "\t" << "&" << Nsig_USTCw << "\t" << "&" << Nsig_USTC_Tot << "(" << 100.00*Nsig_USTCw/Nsig_USTC_Tot << "\\" << "\%)" << "\t" << "&" << Nbkg_Tot_u << "\t" << "&" << 100.00*Nbkg_sig_uw/Nbkg_Tot_u << "\\" << "\%\\" << "\\" << std::endl;   //USTC-Ratio-5
		ratiow << "\\hline" << std::endl;
 		
   	log.close();
   	ratiof.close();
	ratiow.close();*/
	toto.close();
/*****************************code for USTC RPC Signal&Background******************************/ 
	c_SN_ustc->cd();
	TAxis *Xaxis_u = Hist_BG_Ratio_ustc->GetXaxis();	
	auto Yaxis_u = Hist_BG_Ratio_ustc->GetYaxis();	
	
	Xaxis_u->SetTitle("(Mean-MinValue)/RMS");
	Yaxis_u->SetTitle("Events/1");
	Xaxis_u->SetTitleSize(0.05);
	Yaxis_u->SetTitleSize(0.04);
	
	Hist_BG_Ratio_ustc->SetTitle("USTC RPC Signal&Background");
	Hist_BG_Ratio_ustc->SetFillColor(kBlue);
   	Hist_BG_Ratio_ustc->SetFillStyle(3008);
   	Hist_BG_Ratio_ustc->SetStats(0);
	Hist_BG_Ratio_ustc->SetLineColor(kBlue);   	
   	Hist_BG_Ratio_ustc->Draw();
   
   	Hist_SN_Ratio_ustc->SetFillColor(kRed);
 	Hist_SN_Ratio_ustc->SetFillStyle(3003);
   	Hist_SN_Ratio_ustc->SetStats(0);
   	Hist_SN_Ratio_ustc->SetLineColor(kRed);
   	Hist_SN_Ratio_ustc->Draw("same");

   	TLegend *legend_u = new TLegend(.65,.70,.85,.85);
	legend_u->AddEntry(Hist_SN_Ratio_ustc, "Sig(Muon)");
	legend_u->AddEntry(Hist_BG_Ratio_ustc, "Bkg(Noise)");
	legend_u->Draw(); 
 	//c_SN_ustc->SaveAs("../SN_ustc.pdf");
 	
/*****************************code for SJTU RPC Signal&Background******************************/
	c_SN_sjtu->cd();
	TAxis *Xaxis_s = Hist_BG_Ratio_sjtu->GetXaxis();
	auto Yaxis_s = Hist_BG_Ratio_sjtu->GetYaxis();

	Xaxis_s->SetTitle("(Mean-MinValue)/RMS");
	Yaxis_s->SetTitle("Events/1");
	Xaxis_s->SetTitleSize(0.05);
	Yaxis_s->SetTitleSize(0.04);

	Hist_BG_Ratio_sjtu->SetTitle("SJTU RPC Signal&Background");
	Hist_BG_Ratio_sjtu->SetFillColor(kBlue);
   	Hist_BG_Ratio_sjtu->SetFillStyle(3008);
   	Hist_BG_Ratio_sjtu->SetStats(0);
   	Hist_BG_Ratio_sjtu->SetLineColor(kBlue);
   	Hist_BG_Ratio_sjtu->Draw();
   
   	Hist_SN_Ratio_sjtu->SetFillColor(kRed);
   	Hist_SN_Ratio_sjtu->SetFillStyle(3003);
   	Hist_SN_Ratio_sjtu->SetStats(0);
   	Hist_SN_Ratio_sjtu->SetLineColor(kRed);
   	Hist_SN_Ratio_sjtu->Draw("same");

	
	TLegend *legend_s = new TLegend(.65,.70,.85,.85);
	legend_s->AddEntry(Hist_SN_Ratio_sjtu, "Sig(Muon)");
	legend_s->AddEntry(Hist_BG_Ratio_sjtu, "Bkg(Noise)");
	legend_s->Draw();
   //	c_SN_sjtu->SaveAs("../SN_sjtu.pdf");
   	
}   
