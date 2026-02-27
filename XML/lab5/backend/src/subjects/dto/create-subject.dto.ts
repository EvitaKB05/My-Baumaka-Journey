export class CreateSubjectDto {
    src: string;
    title: string;
    text: string;
    modules: [
        {
            src: string;
            title: string;
        }
    ];
}
