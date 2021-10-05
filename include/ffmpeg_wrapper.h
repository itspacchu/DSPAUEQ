using namespace std;
class EQ_FIL_MOD {
    public:
    //http://ffmpeg.org/ffmpeg-filters.html#equalizer
    int filtercount = 0;
    enum precision {_auto,s16,s32,f32,f64};
    string command_gen = "";

    void addEQ(double freq=1000.0,double width=200,double gain_db=-1){
        if(this->filtercount > 0){
            this->command_gen += ",";
        }
        this->command_gen+="equalizer=f="+ to_string(freq) +":t=h:width="+to_string(width)+":g="+to_string(width);
        this->filtercount++;
    }

    string returncommand(){
        return this->command_gen;
    }
};

class FIR_EQ_FIL_MOD {
    public:
    //https://ffmpeg.org/ffmpeg-filters.html#firequalizer
    int filtercount = 0;
    enum precision {_auto,s16,s32,f32,f64};
    string command_gen = "firequalizer=gain_entry='";


    void addEQ(double freq=1000.0,double gain_db=-1){
        if(this->filtercount > 0){
            this->command_gen += ";";
        }
        this->command_gen+="entry("+to_string(freq)+","+to_string(gain_db)+")";
        this->filtercount++;
    }

    string returncommand(){
        return this->command_gen + "'";
    }
};
class FFMPEG {
    public:
    string song_name = "";
    string ffmpegargs = "";
    bool audiofilters = false;
    string set_output_file = "";
    FIR_EQ_FIL_MOD filterboi;
    bool verbose = false;
    bool playlive = false;

    FFMPEG(string song_name,string song_output){
        this->song_name = song_name;
        this->set_output_file = song_output;
    }

    void set_verbose(bool setb){
        this->verbose=setb;
    }

    void addFilter(double freq=1000.0,double gain_db=1){
        this->audiofilters = true;
        this->filterboi.addEQ(freq,gain_db);
    }

    void play_live(bool debug=false){
        this->playlive=true;
        this->run(debug);
    }

    void run(bool debug=false){
        string commandstream = "";
        if(this->song_name != ""){
            commandstream += " -i " + this->song_name;
        }
        if(this->audiofilters){
            commandstream += " -af ";
            commandstream += '"';
            commandstream += this->filterboi.returncommand();
            commandstream += '"';
        }
        commandstream += " " + set_output_file;

        string genCommand = "ffmpeg";
        genCommand += commandstream;
        if(verbose){
            genCommand += " -hide_banner -loglevel error";
        }
        if(playlive){
            genCommand += "-f wav pipe:1 | ffplay -i -";
        }
        if(debug){
            cout << genCommand << endl;
        }else{
            system(genCommand.c_str());
        }
    }
};